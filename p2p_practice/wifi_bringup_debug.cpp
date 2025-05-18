#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <dirent.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <unistd.h>
#include <linux/rfkill.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
bool fileExists(const std::string& path) {
    struct stat st;
    return stat(path.c_str(), &st) == 0;
}
/*
shivaprasad@anonymous:~/chandu/husband/p2p_practice$ g++ -o bring_up_test wifi_bringup_debug.cpp -I/usr/include/libnl3 -lnl-3 -lnl-genl-3

*/
// Helper: Determine if an interface is wireless
bool isWireless(const std::string& iface) {
    // Check for /sys/class/net/<iface>/wireless
    std::string wirelessPath = "/sys/class/net/" + iface + "/wireless";
    if (access(wirelessPath.c_str(), F_OK) == 0) {
        // std::cout << "[DEBUG] " << iface << " has /wireless directory\n";
        return true;
    }
    // Check /sys/class/net/<iface>/uevent for DEVTYPE=wlan
    std::ifstream uevent("/sys/class/net/" + iface + "/uevent");
    std::string line;
    while (std::getline(uevent, line)) {
        if (line.find("DEVTYPE=wlan") != std::string::npos) {
            // std::cout << "[DEBUG] " << iface << " has DEVTYPE=wlan in uevent\n";
            return true;
        }
    }
    return false;
}

// Helper: List wireless interfaces
std::vector<std::string> getWirelessInterfaces() {
    std::vector<std::string> result;
    DIR* dir = opendir("/sys/class/net");
    if (!dir) return result;
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_name[0] == '.') continue;
        std::string iface(entry->d_name);
        std::cout << "[DEBUG] Checking interface: " << iface << std::endl;
        if (isWireless(iface)) {
            std::cout << "[DEBUG] Found wireless interface: " << iface << std::endl;
            result.push_back(iface);
        }
    }
    closedir(dir);
    return result;
}

// Helper: Check if interface is up
bool isInterfaceUp(const std::string& iface) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) return false;
    struct ifreq ifr = {};
    strncpy(ifr.ifr_name, iface.c_str(), IFNAMSIZ-1);
    if (ioctl(sock, SIOCGIFFLAGS, &ifr) < 0) {
        close(sock);
        return false;
    }
    close(sock);
    return (ifr.ifr_flags & IFF_UP);
}

// Helper: Bring interface up
bool bringInterfaceUp(const std::string& iface) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) return false;
    struct ifreq ifr = {};
    strncpy(ifr.ifr_name, iface.c_str(), IFNAMSIZ-1);
    if (ioctl(sock, SIOCGIFFLAGS, &ifr) < 0) {
        close(sock);
        return false;
    }
    ifr.ifr_flags |= IFF_UP;
    bool result = (ioctl(sock, SIOCSIFFLAGS, &ifr) == 0);
    close(sock);
    return result;
}

// Helper: Check rfkill status for all wifi devices
bool isAnyWifiRfkillBlocked() {
    DIR* dir = opendir("/sys/class/rfkill");
    if (!dir) {
        std::cerr << "[WARN] Could not open /sys/class/rfkill. Skipping rfkill check.\n";
        return false;
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_name[0] == '.') continue;
        std::string base = std::string("/sys/class/rfkill/") + entry->d_name;
        std::ifstream typeFile(base + "/type");
        std::string type;
        if (!typeFile.is_open()) continue;
        std::getline(typeFile, type);
        if (type != "wlan") continue;

        std::ifstream softFile(base + "/soft");
        std::ifstream hardFile(base + "/hard");
        int soft = 0, hard = 0;
        if (softFile.is_open()) softFile >> soft;
        if (hardFile.is_open()) hardFile >> hard;

        if (soft || hard) {
            std::cout << "[WARN] Wi-Fi is blocked (rfkill " << entry->d_name
                      << " soft=" << soft << " hard=" << hard << ")\n";
            closedir(dir);
            return true;
        }
    }
    closedir(dir);
    std::cout << "[WARN] Wi-Fi is not blocked (rfkill) good to go?? "<<'\n'; 
    return false;
}

// Helper: List PCI wireless devices (by reading /sys/bus/pci/devices/*/class and vendor)
std::vector<std::pair<std::string, std::string>> getPciWirelessDevices() {
    std::vector<std::pair<std::string, std::string>> result;
    DIR* dir = opendir("/sys/bus/pci/devices");
    if (!dir) return result;
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_name[0] == '.') continue;
        std::string classPath = std::string("/sys/bus/pci/devices/") + entry->d_name + "/class";
        std::ifstream classFile(classPath);
        if (!classFile.is_open()) continue;
        std::string classHex;
        classFile >> classHex;
        if (classHex.length() >= 6 && classHex.substr(classHex.length()-6, 6) == "028000") {
            // 0x0280 is network controller, subclass 0x00 is "network controller: wireless"
            std::string vendorPath = std::string("/sys/bus/pci/devices/") + entry->d_name + "/vendor";
            std::ifstream vendorFile(vendorPath);
            std::string vendorHex;
            vendorFile >> vendorHex;
            result.push_back({entry->d_name, vendorHex});
        }
    }
    closedir(dir);
    return result;
}

// Helper: Print driver info for each wireless interface
void printDriverInfo(const std::string& iface) {
    std::string path = "/sys/class/net/" + iface + "/device/driver";
    char buf[PATH_MAX];
    ssize_t len = readlink(path.c_str(), buf, sizeof(buf)-1);
    if (len > 0) {
        buf[len] = 0;
        std::cout << "[INFO] Interface " << iface << " uses driver: " << buf << std::endl;
    } else {
        std::cout << "[INFO] Could not determine driver for " << iface << std::endl;
    }
}

int main() {
    std::cout << "=== Wireless Interface Bringup Tool ===\n";

    // 1. Check for PCI wireless devices
    auto pciDevs = getPciWirelessDevices();
    if (pciDevs.empty()) {
        std::cout << "[WARN] No PCI wireless devices found. Is your hardware present?\n";
    } else {
        std::cout << "[INFO] PCI wireless devices detected:\n";
        for (const auto& dev : pciDevs) {
            std::cout << "  PCI address: " << dev.first << "  Vendor: " << dev.second << std::endl;
        }
    }

    // 2. Check rfkill status
if (isAnyWifiRfkillBlocked()) {
    std::cout << "[ERROR] Wi-Fi is blocked by rfkill. Please unblock with 'rfkill unblock all'.\n";
    return 1;
}

    // 3. List wireless interfaces
    auto wirelessIfs = getWirelessInterfaces();
    std::cout << "[DEBUG] wirelessIfs.size() = " << wirelessIfs.size() << std::endl;
    if (wirelessIfs.empty()) {
        std::cout << "[ERROR] No wireless interfaces found (checked /sys/class/net/*/wireless and uevent).\n";
        std::cout << "        Possible causes: driver not loaded, hardware disabled, or missing firmware.\n";
        return 1;
    }

    std::cout << "[INFO] Wireless interfaces found:\n";
    for (const auto& iface : wirelessIfs) {
        std::cout << "  " << iface;
        if (isInterfaceUp(iface)) std::cout << " (UP)";
        else std::cout << " (DOWN)";
        std::cout << std::endl;
        printDriverInfo(iface);
    }

    // 4. Bring interfaces up if down
    for (const auto& iface : wirelessIfs) {
        if (!isInterfaceUp(iface)) {
            std::cout << "[INFO] Bringing up interface: " << iface << std::endl;
            if (bringInterfaceUp(iface)) {
                std::cout << "[OK] Interface " << iface << " is now UP.\n";
            } else {
                std::cout << "[FAIL] Could not bring up interface " << iface << ".\n";
            }
        }
    }
    std::cout << "=== Firmware check ===\n";
    if (!fileExists("/lib/firmware/ath10k/QCA9377/hw1.0/firmware-5.bin")) {
    std::cout << "[WARN] ath10k firmware file missing: firmware-5.bin\n";
}

    std::cout << "=== Done ===\n";
    return 0;
}

