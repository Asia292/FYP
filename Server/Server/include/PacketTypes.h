#pragma once

#include "Overloads.h"

using PacketID = sf::Int8;
enum class PacketType
{
	Disconnect = -1, Connect, Heartbeat, Message, KeyPress, KeyRelease, LvlSelectUpdate, StateTransition, PlayerUpdate, LevelUpdate, TimeUpdate, HostDC,
	OutOfBounds // LEAVE ON END
};

void StampPacket(const PacketType& type, sf::Packet& packet);