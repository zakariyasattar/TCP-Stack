#include "TcpConnection.h"

#include <iostream>
#include <vector>
#include <algorithm>

uint32_t TcpConnection::convertIPTo32Bit(std::string IPAddy) {
    std::vector<std::string> IPBlocks {};
    IPBlocks.reserve(4);

    std::string delimiter = ".";

    while(IPAddy.find(delimiter) != std::string::npos) {
        std::string block = IPAddy.substr(0, IPAddy.find(delimiter));
        IPBlocks.push_back(block);

        IPAddy.erase(0, IPAddy.find(delimiter) + delimiter.size());
    }

    // last remaining piece of IPAddy
    IPBlocks.push_back(IPAddy);

    uint32_t result = 0;

    for (const auto& IPBlock : IPBlocks) {
        uint8_t IPBlockInt = static_cast<uint8_t>(std::stoul(IPBlock));

        result = (result << 8) | IPBlockInt;
    }

    return result;
}

std::string TcpConnection::intToBin(uint8_t num) {
    std::string bin;
    bin.reserve(32);

    while(num) {
        bin.push_back(num % 2 + '0');
        num /= 2;
    }

    std::reverse(bin.begin(), bin.end());

    return bin;
}