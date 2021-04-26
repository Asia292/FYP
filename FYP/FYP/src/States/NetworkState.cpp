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

NetworkState::NetworkState(float Height, float Width, std::stack<State*>* States, bool host)
{
	states = States;
	quit = false;
	isHost = host;
	none = nullptr;

	sf::IpAddress ip = "127.0.0.1";
	PortNumber port = 5600;
	
	if (host)
	{
		// Start server
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		if (!CreateProcess(TEXT("Server.exe"),   // the path
			NULL,        // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,              // No creation flags
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&si,            // Pointer to STARTUPINFO structure
			&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
		))
			std::cout << "Can't open server" << std::endl;
	}
	else
	{
		std::cout << "Enter IP: ";
		std::cin >> ip;
		std::cout << "Enter Port: ";
		std::cin >> port;
	}

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
	{
		noServer();
		std::cout << "Failed to connect." << std::endl;
	}
}

NetworkState::~NetworkState()
{
	if (isHost)
	{
		// Shut down server
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}

	if (currState != nullptr)
	{
		delete currState;
		currState = nullptr;
	}

	if (none != nullptr)
	{
		delete none;
		none = nullptr;
	}
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
					if (isHost)
					{
						sf::Packet p;
						StampPacket(PacketType::HostDC, p);
						client.Send(p);
					}
					client.Disconnect();
					quit = true;
				}
			}
		}
		else
			std::cout << "EMPTY!" << std::endl;
	}
	else
	{
		if (none == nullptr)
			noServer();

		none->update(timestep);
	}
}


void NetworkState::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (currState != nullptr)
		currState->draw(target, states);

	if (none != nullptr)
		none->draw(target, states);
}

void NetworkState::processKeyPress(sf::Keyboard::Key code)
{
	if (client.IsConnected())
	{
		sf::Packet p;
		StampPacket(PacketType::KeyPress, p);
		p << code;
		client.Send(p);
	}
	else if (code == sf::Keyboard::Key::Return)
		quit = true;
}

void NetworkState::processKeyRelease(sf::Keyboard::Key code)
{
	if (client.IsConnected())
	{
		sf::Packet p;
		StampPacket(PacketType::KeyRelease, p);
		p << code;
		client.Send(p);
	}
}

void NetworkState::noServer()
{
	currState = nullptr;

	none = new noConnection();
}
