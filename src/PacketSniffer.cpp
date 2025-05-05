#include "PacketSniffer.h"

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/if_tun.h>
#include <net/if.h>
#include <cstring>
#include <vector>


PacketSniffer::~PacketSniffer() {
}

void PacketSniffer::listen() {
    while (true) {
    	std::vector<char> data { m_interface.read() };

    	if(data.size() > 0) {
    		std::cout << data.size() << std::endl;
    	}
    }
}
