/**
 * Packet.
 *
 * @date       April 20, 2015
 *
 * @revisions  May 21, 2015
 *             Improved packet decoding and encoding.
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @notes      This Packet class provides a convenient way for the server and client to communicate with each other.
 *             Included are adding parameters, encoding everything into a string and decoding it back into a packet.
 *
 *             A thanks goes to an answer on Stack Overflow for the convenient string splitter:
 *             http://stackoverflow.com/questions/236129/split-a-string-in-c
 */

#include "Packet.h"

#include <iostream>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

Packet& Packet::combine(const Packet& other)
{
	this->data.reserve(this->data.size() + other.data.size());
	this->data.insert(this->data.end(), other.data.begin(), other.data.end());

	return *this;
}

bool Packet::decode(const char* raw, size_t numOfBytes)
{
	std::string packetContents = std::string(raw, numOfBytes);

	std::cout << packetContents << std::endl;

	data = split(packetContents, DATA_SEPARATOR);
	type = static_cast<PacketType>(get<int>(0));
	data.erase(data.begin());

	return true;
}

size_t Packet::encode(std::string& encoded) const
{
	encoded.clear();

	encoded += static_cast<int>(type) + '0';

	for (const std::string d : data)
	{
		encoded += DATA_SEPARATOR;
		encoded += d;
	}

	// If we want to make all the packets have a fixed length
	/*
	if (encoded.length() < MAX_SIZE)
		encoded += std::string(MAX_SIZE - encoded.length(), '\0');
	*/

	return encoded.length();
}

std::string Packet::toString() const
{
	std::string str;

	str += static_cast<int>(type) + '0';

	for (const std::string d : data)
	{
		str += DATA_SEPARATOR;
		str += d;
	}

	return str;
}
