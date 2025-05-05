#pragma once

#include <stdlib.h>
#include <string>
#include <cstdint>
#include <iostream>

// Connections in TCP are defined by a port number and IP address

class TcpConnection {
private:
    uint16_t m_srcPortNum;
    uint32_t m_srcIPAddy;

    uint32_t m_destPortNum;
    uint32_t m_destIPAddy;

    bool m_client;

public:
    TcpConnection(uint16_t srcPortNum, const std::string& srcIPAddy, uint16_t destPortNum, const std::string& destIPAddy, bool client) : 
        m_srcPortNum(srcPortNum), 
        m_srcIPAddy(convertIPTo32Bit(srcIPAddy)), 
        m_destPortNum(destPortNum),
        m_destIPAddy(convertIPTo32Bit(destIPAddy)),
        m_client(client)
    {
        std::cout << m_srcIPAddy << std::endl;
    }
    
    // convert IP address (string) into 32-bit unsigned int
    uint32_t convertIPTo32Bit(std::string IPAddy);

    // convert 4-byte IP Block to binary and return as sring
    std::string intToBin(uint8_t num);

};