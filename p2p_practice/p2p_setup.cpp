// p2p_setup.cpp
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/nl80211.h>
#include <linux/genetlink.h>
#include <linux/rtnetlink.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <netlink/netlink.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/family.h>
#include <netlink/genl/ctrl.h>
#include <netlink/msg.h>
#include <netlink/attr.h>
//error_tag1 begins
#include <ifaddrs.h>
#include <set>
#include <cstdio>

// Helper: List possible wireless interfaces (by checking /sys/class/net/<iface>/wireless)
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
//error_tag1 ends
/*//HANDELED IN error1_tag 
 error :-
shivaprasad@anonymous:~/chandu/husband/p2p_practice$ sudo ./p2p_setup
[*] Checking if P2P interface exists...
[!] P2P interface does not exist. Creating...
[X] Failed to create P2P interface.
 * */
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
/*
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
    nla_put_u32(msg, NL80211_ATTR_IFINDEX, baseIfidx);
    nla_put_string(msg, NL80211_ATTR_IFNAME, newIface.c_str());
    nla_put_u32(msg, NL80211_ATTR_IFTYPE, NL80211_IFTYPE_P2P_DEVICE);

    int err = nl_send_auto(sock, msg);
    if (err < 0) {
        nlmsg_free(msg);
        nl_socket_free(sock);
        return false;
    }

    nlmsg_free(msg);
    nl_socket_free(sock);
    return true;
}
*/
//error_tag1 begins
// Check if driver supports P2P_DEVICE interface type
bool supportsP2PDevice(const std::string& iface) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "iw phy `iw dev %s info | awk '/wiphy/ {print $2}'` info | grep -q 'Supported interface modes.*P2P-device'", iface.c_str());
    return (system(cmd) == 0);
}

bool createP2PInterface(const std::string& baseIface, const std::string& newIface) {
    struct nl_sock *sock = nl_socket_alloc();
    if (!sock) {
        std::cerr << "[X] nl_socket_alloc failed\n";
        return false;
    }

    if (genl_connect(sock)) {
        std::cerr << "[X] genl_connect failed\n";
        nl_socket_free(sock);
        return false;
    }

    int driver_id = genl_ctrl_resolve(sock, "nl80211");
    if (driver_id < 0) {
        std::cerr << "[X] genl_ctrl_resolve failed: nl80211 not found\n";
        nl_socket_free(sock);
        return false;
    }

    struct nl_msg *msg = nlmsg_alloc();
    if (!msg) {
        std::cerr << "[X] nlmsg_alloc failed\n";
        nl_socket_free(sock);
        return false;
    }

    int baseIfidx = if_nametoindex(baseIface.c_str());
    if (baseIfidx == 0) {
        std::cerr << "[X] Base interface not found: " << baseIface << "\n";
        nlmsg_free(msg);
        nl_socket_free(sock);
        return false;
    }

    genlmsg_put(msg, 0, 0, driver_id, 0, 0, NL80211_CMD_NEW_INTERFACE, 0);
    nla_put_u32(msg, NL80211_ATTR_IFINDEX, baseIfidx);
    nla_put_string(msg, NL80211_ATTR_IFNAME, newIface.c_str());
    nla_put_u32(msg, NL80211_ATTR_IFTYPE, NL80211_IFTYPE_P2P_DEVICE);

    int err = nl_send_auto(sock, msg);
    if (err < 0) {
        std::cerr << "[X] nl_send_auto failed: " << err << "\n";
        nlmsg_free(msg);
        nl_socket_free(sock);
        return false;
    }

    // Wait for ACK
    err = nl_wait_for_ack(sock);
    if (err < 0) {
        std::cerr << "[X] nl_wait_for_ack failed: " << err << "\n";
        nlmsg_free(msg);
        nl_socket_free(sock);
        return false;
    }

    nlmsg_free(msg);
    nl_socket_free(sock);
    return true;
}
//error_tag1 ends
bool isWpaSupplicantRunning() {
    return (system("pgrep wpa_supplicant > /dev/null") == 0);
}

bool startWpaSupplicant(const std::string& iface) {
    std::string command = "wpa_supplicant -B -i " + iface + " -c /etc/wpa_supplicant.conf";
    return (system(command.c_str()) == 0);
}

bool sendP2PFindCommand(const std::string& iface) {
    std::string ctrl_path = "/var/run/wpa_supplicant/" + iface;
    int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sock < 0) return false;

    struct sockaddr_un addr = {};
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, ctrl_path.c_str(), sizeof(addr.sun_path) - 1);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect");
        close(sock);
        return false;
    }

    const char *cmd = "P2P_FIND";
    if (send(sock, cmd, strlen(cmd), 0) < 0) {
        perror("send");
        close(sock);
        return false;
    }

    char buf[4096] = {};
    int len = recv(sock, buf, sizeof(buf) - 1, 0);
    if (len < 0) {
        perror("recv");
        close(sock);
        return false;
    }

    buf[len] = '\0';
    std::cout << "[P2P_FIND response] " << buf << std::endl;

    close(sock);
    return true;
}

int main() {
//errot_tag begin	
    // 1. Auto-detect wireless base interface
    auto wirelessIfs = getWirelessInterfaces();
    if (wirelessIfs.empty()) {
        std::cerr << "[X] No wireless interfaces found on this system.\n";
        return 1;
    }
    std::string baseIface = wirelessIfs[0];
    std::string p2pIface = "p2p-" + baseIface + "-0";

    std::cout << "[*] Using base wireless interface: " << baseIface << std::endl;

    // 2. Check for P2P support
    if (!supportsP2PDevice(baseIface)) {
        std::cerr << "[X] The interface " << baseIface << " does not support P2P_DEVICE mode.\n";
        return 1;
    }
//error_tag1 ends
/*error_tag1-->previous code
    const std::string baseIface = "wlan0";
    const std::string p2pIface = "p2p-wlan0-0";
*/
    std::cout << "[*] Checking if P2P interface exists...\n";
    if (!interfaceExists(p2pIface)) {
        std::cout << "[!] P2P interface does not exist. Creating...\n";
        if (!createP2PInterface(baseIface, p2pIface)) {
            std::cerr << "[X] Failed to create P2P interface.\n";
            return 1;
        }
    }

    if (!isInterfaceUp(p2pIface)) {
        std::cout << "[*] Interface is down. Bringing it up...\n";
        if (!bringInterfaceUp(p2pIface)) {
            std::cerr << "[X] Failed to bring up interface.\n";
            return 1;
        }
    }

    std::cout << "[*] Interface is ready. Checking for wpa_supplicant...\n";
    if (!isWpaSupplicantRunning()) {
        std::cout << "[!] wpa_supplicant not running. Starting...\n";
        if (!startWpaSupplicant(p2pIface)) {
            std::cerr << "[X] Failed to start wpa_supplicant.\n";
            return 1;
        }
    }

    std::cout << "[*] Sending P2P_FIND command...\n";
    if (!sendP2PFindCommand(p2pIface)) {
        std::cerr << "[X] Failed to send P2P_FIND command.\n";
        return 1;
    }

    std::cout << "[✓] P2P_FIND command sent successfully.\n";
    return 0;
}

