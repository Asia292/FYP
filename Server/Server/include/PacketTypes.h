#pragma once

#include <SFML/Network.hpp>

using PacketID = sf::Int8;
enum class PacketType
{
	Disconnect = -1, Connect, Heartbeat, Message, KeyPress, KeyRelease, LevelNumber,
	OutOfBounds // LEAVE ON END
};

void StampPacket(const PacketType& type, sf::Packet& packet);