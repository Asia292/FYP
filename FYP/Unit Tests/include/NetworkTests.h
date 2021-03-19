#pragma once
#include <gtest/gtest.h>
#define private public
#define protected public
#include "NetworkState.h"
//#include "ServerMock.h"

/*
	HOW TO
	- Add client
	- Client DC

	- Check corrosponding function called for packet

	- Wait, will I have to mock the other functions for this....
		- Check info passed up the function chain
			- Functions called in sequence
		- Check what packet is returned
			- Check correct info in packet
				- Exact values if known
				- Structure type if not?
	
*/


inline void mockHandler(const PacketID& l_id, sf::Packet& l_packet, ClientID cID, State *currState)
{
	//std::cout << "Packet recieved" << std::endl;
	ClientID id = cID;
	if (id >= 0)
	{
		if ((PacketType)l_id == PacketType::KeyPress)
		{
			int recieve;
			l_packet >> recieve;

			currState->processNetworkKeyPress(recieve, nullptr, id);
		}
		else if ((PacketType)l_id == PacketType::KeyRelease)
		{
			int recieve;
			l_packet >> recieve;

			currState->processNetworkKeyRelease(recieve, nullptr, id);
		}
	}
	else
	{
		if ((PacketType)l_id == PacketType::Connect)
		{
			ClientID id = cID;
			if (id != -1)
			{
				sf::Packet packet;
				StampPacket(PacketType::Connect, packet);
				//l_server->Send(id, packet);
			}
			else
			{
				//l_server->RemoveClient(id);
			}
		}
	}
}
