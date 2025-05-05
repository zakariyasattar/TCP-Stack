#pragma once

#include <fstream>
#include <vector>
#include <mutex>

class TunInterface {
private:
	int m_fd;
	std::mutex m_mtx;

public:
	TunInterface() : m_fd(openTunInterface("tun0")) {}

	std::vector<char> read();
	void write(std::vector<char>& buffer);
	int openTunInterface(const std::string& ifname);
};