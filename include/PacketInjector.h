#pragma once

#include <fcntl.h>
#include <unistd.h>
#include <cstdint>
#include <sys/ioctl.h>
#include <linux/if_tun.h>
#include <net/if.h>
#include <cstring>
#include <iostream>
#include <vector>

#include "TunInterface.h"

class PacketInjector {
private:
	TunInterface& m_interface;

public:
    PacketInjector(TunInterface& interface) : m_interface(interface) {}

    ~PacketInjector() {}

    void inject() {
    	while(true) {
    		std::vector<char> packet_buffer(40, 0);

    		packet_buffer[0] = 0x45; // version = 4 (IPv4), IHL = 5
    		packet_buffer[1] = 0x00;
    		packet_buffer[2] = 0x28; // total length
    		packet_buffer[3] = 0x00;
    		packet_buffer[4] = 0x00; // ID
    		packet_buffer[5] = 0x00;
    		packet_buffer[6] = 0x40;  // Flags+Frag offset
			packet_buffer[7] = 0x00;
			packet_buffer[8] = 0x40;  // TTL
			packet_buffer[9] = 0x06;  // Protocol TCP (instead of ICMP=1)

			packet_buffer[10] = 0x00; // Checksum placeholder
			packet_buffer[11] = 0x00;

			packet_buffer[12] = 0x7f; // Src IP 127.0.0.1
			packet_buffer[13] = 0x00;
			packet_buffer[14] = 0x00;
			packet_buffer[15] = 0x01;
			packet_buffer[16] = 0x7f; // Dst IP 127.0.0.1
			packet_buffer[17] = 0x00;
			packet_buffer[18] = 0x00;
			packet_buffer[19] = 0x01;

			uint16_t checksum {}; 

			// checksum is calculated using 16-bit words
			for(int i = 0; i < packet_buffer.size(); i++) {
				uint16_t word { packet_buffer[i] << 8 | packet_buffer[i + 1] };

				checksum += word; 

				if(checksum > 0xffff) { // > 16
					checksum = (checksum & 0xFFFF) + 1;
				}
			}

			checksum = ~checksum;

			packet_buffer[10] = (checksum >> 8) & 0xFF;
			packet_buffer[11] = checksum & 0xFF;

        	m_interface.write(packet_buffer);
    	}
    }
};
