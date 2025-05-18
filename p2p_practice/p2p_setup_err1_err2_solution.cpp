#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <netlink/netlink.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/family.h>
#include <netlink/genl/ctrl.h>
#include <netlink/msg.h>
#include <netlink/attr.h>
#include <ifaddrs.h>
#include <linux/nl80211.h>
#include <fcntl.h>
#include <ctime>
#include <sys/time.h>  // for struct timeval

void monitorWpaSupplicantEvents(const std::string& iface, int duration_seconds = 30) {
    // Create a unique client socket path
    std::string client_path = "/tmp/wpa_ctrl_" + iface + "_" + std::to_string(getpid());

    // Control socket path for wpa_supplicant
    std::string ctrl_path = "/var/run/wpa_supplicant/" + iface;

    int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return;
    }

    // Bind the client socket
    struct sockaddr_un client_addr = {};
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, client_path.c_str(), sizeof(client_addr.sun_path) - 1);
    unlink(client_path.c_str()); // Remove if exists
    if (bind(sock, (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0) {
        perror("bind");
        close(sock);
        return;
    }

    // Connect to the wpa_supplicant control socket
    struct sockaddr_un serv_addr = {};
    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, ctrl_path.c_str(), sizeof(serv_addr.sun_path) - 1);
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        close(sock);
        unlink(client_path.c_str());
        return;
    }

    // Attach for event messages
const char* attach_cmd = "ATTACH";    
if (send(sock, attach_cmd, strlen(attach_cmd), 0) < 0) {
    perror("send ATTACH");
    close(sock);
    unlink(client_path.c_str());
    return;
}

char attach_resp[100] = {};
int len = recv(sock, attach_resp, sizeof(attach_resp) - 1, 0);
if (len <= 0) {
    perror("recv after ATTACH");
    close(sock);
    unlink(client_path.c_str());
    return;
}
attach_resp[len] = '\0';
std::cout << "[ATTACH RESPONSE] " << attach_resp << std::endl;


    std::cout << "[*] Monitoring wpa_supplicant events for " << duration_seconds << " seconds...\n";
    time_t start_time = time(nullptr);

    while (time(nullptr) - start_time < duration_seconds) {
        char buf[4096] = {};
        int len = recv(sock, buf, sizeof(buf) - 1, 0);
        if (len > 0) {
            buf[len] = '\0';
            std::string msg(buf);
            std::cout << "[RECV] " << msg << std::endl;
        } else if (len < 0) {
            perror("recv");
            break;
        }
    }

    // Detach and clean up
    const char* detach_cmd = "DETACH";
    send(sock, detach_cmd, strlen(detach_cmd), 0);
    close(sock);
    unlink(client_path.c_str());
    std::cout << "[*] Done monitoring events.\n";
}

// Helper: List possible wireless interfaces
std::vector<std::string> getWirelessInterfaces() {
    std::vector<std::string> result;
    struct ifaddrs *ifaddr, *ifa;
    if (getifaddrs(&ifaddr) == -1) return result;
    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (ifa->ifa_name == nullptr) continue;
        std::string path = "/sys/class/net/" + std::string(ifa->ifa_name) + "/wireless";
        if (access(path.c_str(), F_OK) == 0) {
            result.push_back(ifa->ifa_name);
        }
    }
    freeifaddrs(ifaddr);
    return result;
}

bool interfaceExists(const std::string& iface) {
    return if_nametoindex(iface.c_str()) != 0;
}

bool isInterfaceUp(const std::string& iface) {
    std::ifstream operstate("/sys/class/net/" + iface + "/operstate");
    if (!operstate.is_open()) return false;
    std::string state;
    operstate >> state;
    return state == "up";
}

bool bringInterfaceUp(const std::string& iface) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) return false;

    struct ifreq ifr = {};
    strncpy(ifr.ifr_name, iface.c_str(), IFNAMSIZ);
    if (ioctl(sock, SIOCGIFFLAGS, &ifr) < 0) {
        close(sock);
        return false;
    }

    ifr.ifr_flags |= IFF_UP;
    bool result = (ioctl(sock, SIOCSIFFLAGS, &ifr) == 0);
    close(sock);
    return result;
}

// Try to create a P2P interface. Return true if succeeded.
bool createP2PInterface(const std::string& baseIface, const std::string& newIface) {
    struct nl_sock *sock = nl_socket_alloc();
    if (!sock) return false;

    if (genl_connect(sock)) {
        nl_socket_free(sock);
        return false;
    }

    int driver_id = genl_ctrl_resolve(sock, "nl80211");
    if (driver_id < 0) {
        nl_socket_free(sock);
        return false;
    }

    struct nl_msg *msg = nlmsg_alloc();
    if (!msg) {
        nl_socket_free(sock);
        return false;
    }

    int baseIfidx = if_nametoindex(baseIface.c_str());
    if (baseIfidx == 0) {
        nlmsg_free(msg);
        nl_socket_free(sock);
        return false;
    }

    genlmsg_put(msg, 0, 0, driver_id, 0, 0, NL80211_CMD_NEW_INTERFACE, 0);
    nla_put_u32(msg, 1 /* NL80211_ATTR_IFINDEX */, baseIfidx);
    nla_put_string(msg, 3 /* NL80211_ATTR_IFNAME */, newIface.c_str());
    nla_put_u32(msg, 4 /* NL80211_ATTR_IFTYPE */, 8 /* NL80211_IFTYPE_P2P_DEVICE */);

    int err = nl_send_auto(sock, msg);
    nlmsg_free(msg);
    if (err < 0) {
        nl_socket_free(sock);
        return false;
    }

    // Wait for ACK
    err = nl_wait_for_ack(sock);
    nl_socket_free(sock);
    return err >= 0;
}

bool isWpaSupplicantRunning(const std::string& iface) {
    // Check if the wpa_supplicant control socket exists for this interface
    std::string ctrl_path = "/var/run/wpa_supplicant/" + iface;
    return (access(ctrl_path.c_str(), F_OK) == 0);
}

bool startWpaSupplicant(const std::string& iface) {
    // Use -B for background, -Dnl80211 for modern drivers
    std::string command = "wpa_supplicant -B -Dnl80211 -i " + iface + " -c /etc/wpa_supplicant.conf";
    std::cout << "[*] Starting wpa_supplicant: " << command << std::endl;
    return (system(command.c_str()) == 0);
}



bool sendP2PFindCommand(const std::string& iface) {
    std::string ctrl_path = "/var/run/wpa_supplicant/" + iface;
    std::string client_path = "/tmp/wpa_ctrl_" + iface + "_" + std::to_string(getpid());

    int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("[ERROR] socket creation");
        return false;
    }

    // Set a timeout for recv
    struct timeval tv = {3, 0};
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    // Bind to client path
    struct sockaddr_un local = {};
    local.sun_family = AF_UNIX;
    strncpy(local.sun_path, client_path.c_str(), sizeof(local.sun_path) - 1);
    unlink(client_path.c_str());
    if (bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0) {
        perror("[ERROR] bind");
        close(sock);
        return false;
    }

    // Destination address (wpa_supplicant control socket)
    struct sockaddr_un remote = {};
    remote.sun_family = AF_UNIX;
    strncpy(remote.sun_path, ctrl_path.c_str(), sizeof(remote.sun_path) - 1);

    const char *cmd = "P2P_FIND";
    std::cout << "[DEBUG] Sending command: " << cmd << std::endl;
    if (sendto(sock, cmd, strlen(cmd), 0, (struct sockaddr*)&remote, sizeof(remote)) < 0) {
        perror("[ERROR] sendto");
        close(sock);
        unlink(client_path.c_str());
        return false;
    }

    char buf[4096] = {};
    socklen_t remote_len = sizeof(remote);
    int len = recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&remote, &remote_len);
    if (len < 0) {
        perror("[ERROR] recvfrom");
        close(sock);
        unlink(client_path.c_str());
        return false;
    }

    buf[len] = '\0';
    std::cout << "[P2P_FIND response] " << buf << std::endl;

    close(sock);
    unlink(client_path.c_str());
    return true;
}


int main() {
    auto wirelessIfs = getWirelessInterfaces();
    if (wirelessIfs.empty()) {
        std::cerr << "[X] No wireless interfaces found.\n";
        return 1;
    }
    std::string baseIface = wirelessIfs[0];
    std::string p2pIface = "p2p-" + baseIface + "-0";
    std::string useIface = p2pIface;

    std::cout << "[*] Using base wireless interface: " << baseIface << std::endl;

    bool p2pCreated = false;
    if (!interfaceExists(p2pIface)) {
        std::cout << "[*] Attempting to create P2P interface...\n";
        p2pCreated = createP2PInterface(baseIface, p2pIface);
        if (!p2pCreated) {
            std::cout << "[!] Could not create P2P interface. Falling back to base interface for P2P operations.\n";
            useIface = baseIface;
        }
    } else {
        p2pCreated = true;
    }

    if (!isInterfaceUp(useIface)) {
        std::cout << "[*] Interface " << useIface << " is down. Bringing it up...\n";
        if (!bringInterfaceUp(useIface)) {
            std::cerr << "[X] Failed to bring up interface.\n";
            return 1;
        }
    }

    std::cout << "[*] Checking for wpa_supplicant on " << useIface << "...\n";
    if (!isWpaSupplicantRunning(useIface)) {
        std::cout << "[!] wpa_supplicant not running. Starting...\n";
        if (!startWpaSupplicant(useIface)) {
            std::cerr << "[X] Failed to start wpa_supplicant.\n";
            return 1;
        }
        // Wait a moment for wpa_supplicant to create the control socket
        sleep(2);
    }

    std::cout << "[*] Sending P2P_FIND command to " << useIface << "...\n";
    if (!sendP2PFindCommand(useIface)) {
        std::cerr << "[X] Failed to send P2P_FIND command.\n";
        return 1;
    }

    std::cout << "[✓] P2P_FIND command sent successfully on " << useIface << ".\n";
    monitorWpaSupplicantEvents(useIface, 30); // Monitor for 30 seconds
    return 0;
}
