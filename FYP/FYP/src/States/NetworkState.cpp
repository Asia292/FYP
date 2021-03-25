#include "NetworkState.h"

void NetworkState::HandlePackets(const PacketID & id, sf::Packet & packet, Client * client)
{
	if ((PacketType)id == PacketType::Message)
	{
		std::string message;
		packet >> message;
		std::cout << message << std::endl;
	}
	else if ((PacketType)id == PacketType::LvlSelectUpdate)
	{
		LevelSelectUpdate update;
		packet >> update;
		currState->levelSelectUpdate(update.currLevel, update.back);
	}
	else if ((PacketType)id == PacketType::PlayerUpdate)
	{
		PlayerUpdate update;
		packet >> update;
		currState->playerUpdate(update.player, update.texture, update.frame, update.flip, update.dead, update.position);
	}
	else if ((PacketType)id == PacketType::LevelUpdate)
	{
		LevelUpdate update;
		packet >> update;
		currState->levelUpdate(update.object, update.index, update.texture, update.frame, update.angle, update.position);
	}
	else if ((PacketType)id == PacketType::StateTransition)
	{
		bool push;
		packet >> push;
		currState->stateTransition(push);
	}
	else if ((PacketType)id == PacketType::TimeUpdate)
	{
		LevelSelectUpdate time;
		packet >> time;
		currState->timeUpdate(time.currLevel, time.back);
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
		
	client.SetServerInfo(ip, port);
	client.Setup(&NetworkState::HandlePackets, this);
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
			//std::cout << "NOT EMPTY!" << std::endl;
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
					client.Disconnect();
				}
			}
		}
		else
			std::cout << "EMPTY!" << std::endl;
	}
	else
	{
		delete currState;
		quit = true;
	}
}


void NetworkState::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (currState != nullptr)
		currState->draw(target, states);
}

void NetworkState::processKeyPress(sf::Keyboard::Key code)
{
	sf::Packet p;
	StampPacket(PacketType::KeyPress, p);
	p << code;
	client.Send(p);
}

void NetworkState::processKeyRelease(sf::Keyboard::Key code)
{
	sf::Packet p;
	StampPacket(PacketType::KeyRelease, p);
	p << code;
	client.Send(p);
}
