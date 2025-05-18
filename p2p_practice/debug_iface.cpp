#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <string>
#include <fstream>

int main() {
    std::cout << "=== Wireless Interface Debug ===\n";
    DIR* dir = opendir("/sys/class/net");
    if (!dir) {
        std::cerr << "[ERROR] Cannot open /sys/class/net\n";
        return 1;
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_name[0] == '.') continue;
        std::string iface(entry->d_name);
        std::cout << "Checking interface: " << iface << std::endl;
        std::string wirelessPath = "/sys/class/net/" + iface + "/wireless";
        if (access(wirelessPath.c_str(), F_OK) == 0) {
            std::cout << "  [FOUND] " << iface << " has /wireless directory" << std::endl;
        } else {
            std::cout << "  [NOT FOUND] " << iface << " has no /wireless directory" << std::endl;
        }
        // Check uevent
        std::ifstream uevent("/sys/class/net/" + iface + "/uevent");
        std::string line;
        bool found = false;
        while (std::getline(uevent, line)) {
            if (line.find("DEVTYPE=wlan") != std::string::npos) {
                std::cout << "  [FOUND] " << iface << " has DEVTYPE=wlan in uevent" << std::endl;
                found = true;
            }
        }
        if (!found) std::cout << "  [NOT FOUND] " << iface << " has no DEVTYPE=wlan in uevent" << std::endl;
    }
    closedir(dir);
    std::cout << "=== End Debug ===\n";
    return 0;
}

