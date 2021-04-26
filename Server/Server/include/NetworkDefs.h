#pragma once

#include "PacketTypes.h"
#include <functional>
#include <iostream>
#include <unordered_map>

enum class Network
{
	HighestTimestamp = 2147483647, ClientTimeout = 10000, ServerPort = 5600, ClientPort = 25565, NullID = -1
};

using ClientID = int;
using PortNumber = unsigned short;