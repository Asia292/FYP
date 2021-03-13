#include "Server.h"
#include "LevelSelectState.h"

State *currState;

void Handler(sf::IpAddress& l_ip, const PortNumber& l_port, const PacketID& l_id, sf::Packet& l_packet, Server* l_server)
{ 
	//std::cout << "Packet recieved" << std::endl;
	ClientID id = l_server->GetClientID(l_ip, l_port); 
	if (id >= 0) 
	{ 
		if ((PacketType)l_id == PacketType::Disconnect) 
		{ 
			l_server->RemoveClient(l_ip, l_port); 
			sf::Packet p; 
			StampPacket(PacketType::Message, p);
			std::string message; message = "Client left! " + l_ip.toString() + ":" + std::to_string(l_port); p << message; 
			l_server->Broadcast(p, id); 
		} 
		else if ((PacketType)l_id == PacketType::Message) 
		{ 
			std::string receivedMessage; 
			l_packet >> receivedMessage; 
			std::string message = l_ip.toString() + ":" + std::to_string(l_port) + " :" + receivedMessage; 
			sf::Packet p; 
			StampPacket(PacketType::Message, p); 
			p << message;
			l_server->Broadcast(p, id); 
		} 
		else if ((PacketType)l_id == PacketType::KeyPress)
		{
			int recieve;
			l_packet >> recieve;

			currState->processNetworkKeyPress(recieve, l_server, id);
		}
		else if ((PacketType)l_id == PacketType::KeyRelease)
		{
			int recieve;
			l_packet >> recieve;

			currState->processNetworkKeyRelease(recieve, l_server, id);
		}
	} 
	else 
	{ 
		if ((PacketType)l_id == PacketType::Connect) 
		{ 
			ClientID id = l_server->AddClient(l_ip, l_port); 
			if (id != -1)
			{
				sf::Packet packet;
				StampPacket(PacketType::Connect, packet);
				l_server->Send(id, packet);
			}
			else
			{
				l_server->RemoveClient(id);
			}
		} 
	} 
}


void CommandProcess(Server* l_server) 
{ 
	while (l_server->IsRunning()) 
	{ 
		std::string str; 
		std::getline(std::cin, str); 
		if (str == "!quit") 
		{ 
			l_server->Stop(); 
			break; 
		} 
		else if (str == "dc") 
		{ 
			l_server->DisconnectAll(); 
			std::cout << "DC..." << std::endl; 
		} 
		else if (str == "list") 
		{ 
			std::cout << l_server->GetClientCount() << " clients online:" << std::endl; 
			std::cout << l_server->GetClientList() << std::endl; 
		} 
	} 
}


int main() 
{ 
	float fFrameTime = 1.f / 60.f;
	std::stack<State *> states;

	Server server(Handler);
	states.push(new LevelSelectState(1024, 800, &states, &server));
	currState = states.top();
	if (server.Start()) 
	{ 
		//sf::Thread c(&CommandProcess, &server); 
		//c.launch(); 
		sf::Clock serverClock; 
		sf::Clock gameClock;
		//clock.restart(); 
		while (server.IsRunning()) 
		{ 
			float m_fElapsedTime = gameClock.getElapsedTime().asSeconds();
			// If a frame has past the update the physics
			if (m_fElapsedTime > fFrameTime)
			{
				if (!states.empty())
				{
					currState = states.top();
					currState->update(m_fElapsedTime);

					if (currState->getQuit())
					{
						delete states.top();
						states.pop();

						if (!states.empty())
							currState = states.top();
						else
						{
							currState = nullptr;
							delete currState;
						}
					}
				}
				gameClock.restart();
			}
			server.Update(serverClock.restart());
		} 
		std::cout << "Stopping server..." << std::endl; 
	} 
	system("PAUSE"); 
	return 0; 
}
