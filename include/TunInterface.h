#pragma once

#include <fstream>
#include <vector>
#include <iostream>
#include <mutex>

#include <fcntl.h>        // for O_RDWR
#include <unistd.h>       // for open(), close(), read(), write()
#include <sys/ioctl.h>    // for ioctl()
#include <linux/if_tun.h> // for IFF_TAP, IFF_NO_PI, TUNSETIFF
#include <net/if.h>       // for ifreq, IFNAMSIZ
#include <cstring>        // for std::memset, std::strncpy

class TunInterface {
private:
	int m_fd;
	std::mutex m_mtx;

public:
	TunInterface() { 
		const std::string& ip = "10.0.0.1/24";
		m_fd = openTunInterface("tun0");

		if (m_fd >= 0) {
            std::cout << "TUN interface created with fd: " << m_fd << std::endl;
            // Configure the interface (bring it up and set IP)
            if (!configureInterface(ip)) {
                std::cerr << "Failed to configure TUN interface" << std::endl;
            }
        } else {
            std::cerr << "Failed to create TUN interface" << std::endl;
        }
	}

	std::vector<char> read();
	void write(std::vector<char>& buffer);
	int openTunInterface(const std::string& ifname);

	bool configureInterface(const std::string& ip) {
        // Bring the interface up
        std::string cmd = "ip link set dev tun0 up";
        if (system(cmd.c_str()) != 0) {
            perror("Failed to bring interface up");
            return false;
        }

        // Set IP address
        cmd = "ip addr add " + ip + " dev tun0";
        if (system(cmd.c_str()) != 0) {
            perror("Failed to set IP address");
            return false;
        }

        std::cout << "Configured TUN interface with IP: " << ip << std::endl;
        return true;
    }

    bool isUp() {
        struct ifreq ifr;
        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) {
            perror("socket");
            return false;
        }

        memset(&ifr, 0, sizeof(ifr));
        strncpy(ifr.ifr_name, "tun0", IFNAMSIZ - 1);

        if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0) {
            perror("ioctl SIOCGIFFLAGS");
            close(sockfd);
            return false;
        }
        
        close(sockfd);
        return (ifr.ifr_flags & IFF_UP) != 0;
    }
};