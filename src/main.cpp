#include <iostream>
#include <TcpConnection.h>

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

    // test
}