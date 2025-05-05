#pragma once

#include <net/if.h>
#include "TunInterface.h"

class PacketSniffer {
private:
	TunInterface& m_interface;

public:
	PacketSniffer(TunInterface& interface) : m_interface(interface) {}
	~PacketSniffer();

	void listen();

};