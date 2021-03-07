#include "NetworkState.h"

void HandlePacket(const PacketID & id, sf::Packet & packet, Client * client)
{
	if ((PacketType)id == PacketType::Message)
	{
		std::string message;
		packet >> message;
		std::cout << message << std::endl;
	}
	else if ((PacketType)id == PacketType::Disconnect)
		client->Disconnect();
}


NetworkState::NetworkState(float Height, float Width, std::stack<State*>* States)
{
	states = States;
	quit = false;

	sf::IpAddress ip = "127.0.0.1";
	PortNumber port = 5600;
		
	/*std::cout << "Enter server IP: ";
	std::cin >> ip;
	std::cout << "Enter server port: ";
	std::cin >> port;*/
	
	client.SetServerInfo(ip, port);
	client.Setup(&HandlePacket);
	//sf::Thread c(&CommandProcess, &client);
	//sf::Thread l(&Client::Listen);
	if (client.Connect())
	{
		//c.launch();
		//l.launch();
		clock.restart();
		std::cout << "Connected" << std::endl;
		netStates.push(new LevelSelectState(Width, Height, &netStates));
		currState = netStates.top();
	}
	else
		std::cout << "Failed to connect." << std::endl;
}

NetworkState::~NetworkState()
{

}

void NetworkState::update(float timestep)
{
	if (client.IsConnected())
	{
		client.Update(clock.restart());


		if (!netStates.empty())
		{
			currState = netStates.top();
			currState->update(timestep);

			if (currState->getQuit())
			{
				delete netStates.top();
				netStates.pop();

				if (!netStates.empty())
					currState = netStates.top();
				else
				{
					currState = nullptr;
					delete currState;
					quit = true;
				}
			}
		}
	}
}

void NetworkState::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	currState->draw(target, states);
}

void NetworkState::processKeyPress(sf::Keyboard::Key code)
{
}

void NetworkState::processKeyRelease(sf::Keyboard::Key code)
{
}
