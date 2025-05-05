#include "TunInterface.h"

#include <iostream>

int TunInterface::openTunInterface(const std::string& ifname) {
    int fd = ::open("/dev/net/tun", O_RDWR);
    if (fd < 0) {
        perror("open /dev/net/tun");
        return -1;
    }

    struct ifreq ifr;
    std::memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
    std::strncpy(ifr.ifr_name, ifname.c_str(), IFNAMSIZ);

    if (ioctl(fd, TUNSETIFF, (void *)&ifr) < 0) {
        perror("ioctl TUNSETIFF");
        close(fd);
        return -1;
    }

    // SET NONBLOCK AFTER ioctl
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL");
        close(fd);
        return -1;
    }
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL O_NONBLOCK");
        close(fd);
        return -1;
    }

    std::cout << "Opened TUN interface " << ifname << "\n";
    return fd;
}

std::vector<char> TunInterface::read() {
    // std::lock_guard<std::mutex> lock (m_mtx);

    std::vector<char> buffer(2048);
    int nbytes = ::read(m_fd, buffer.data(), buffer.size());

    if(nbytes > 0) {
        buffer.resize(nbytes);
    } 
    else {
        buffer.clear();
    }

    return buffer;
}

void TunInterface::write(std::vector<char>& buffer) {
    // std::unique_lock<std::mutex> lock (m_mtx);
    ::write(m_fd, buffer.data(), buffer.size());

    // std::cout << TunInterface::read().size() << std::endl;
}