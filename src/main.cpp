#include <iostream>
#include <net/if.h>
#include <thread>

#include "TcpConnection.h"
#include "PacketSniffer.h"
#include "PacketInjector.h"
#include "TunInterface.h"

using namespace std;

// File | Purpose
// TcpConnection.cpp | Handles a full TCP connection (handshake, send/recv, close) — acts as both client or server
// TcpSegment.cpp | Parses and builds TCP segments (headers, options, etc.)
// TapInterface.cpp | Reads/writes Ethernet frames via TAP device
// ArpResolver.cpp | Handles IP → MAC address resolution manually
// PacketSniffer.cpp | Captures incoming packets and dispatches them
// PacketInjector.cpp | Sends packets you manually craft

int main() {
    bool isClient { true }; // client initializes SYN

    TcpConnection client {500, "192.168.100.124", 880, "192.168.11.34", isClient};
    TcpConnection server {880, "192.168.11.34", 500, "192.168.100.124", !isClient};

    TunInterface interface {};

    std::thread sniff {[&]() {
        PacketSniffer sniffer (interface);
        sniffer.listen();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }};

    std::thread inject {[&]() {
        PacketInjector injector(interface);
        injector.inject();
    }};

    sniff.join();
    inject.join();

    // std::cout << if_nametoindex("tap0") << std::endl;


    // test
}