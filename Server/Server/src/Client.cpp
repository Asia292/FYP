#include "Client.h"

Client::Client() : listenThread(&Client::Listen, this), commandThread(&Client::CommandProcess, this)
{
}

Client::~Client()
{
	socket.unbind();
}

bool Client::Connect()
{
	if (connected)
		return false;

	socket.bind(sf::Socket::AnyPort);
	sf::Packet p;
	StampPacket(PacketType::Connect, p);
	p << playerName;

	if (socket.send(p, serverIP, serverPort) != sf::Socket::Done)
	{
		socket.unbind();
		return false;
	}

	socket.setBlocking(false);
	p.clear();
	sf::IpAddress recvIP;
	PortNumber recvPort;
	sf::Clock timer;
	timer.restart();

	while (timer.getElapsedTime().asMilliseconds() < CONNECT_TIMEOUT)
	{
		sf::Socket::Status s = socket.receive(p, recvIP, recvPort);

		if (s != sf::Socket::Done)
			continue;

		if (recvIP != serverIP)
			continue;

		PacketID id;

		if (!(p >> id))
			break;

		if ((PacketType)id != PacketType::Connect)
			continue;

		packetHandler(id, p, this);
		connected = true;
		socket.setBlocking(true);
		lastHeartbeat = serverTime;
		listenThread.launch();
		return true;
	}
	std::cout << "Connection attempt failed! Server info: " << serverIP << ":" << serverPort << std::endl;
	socket.unbind();
	socket.setBlocking(true);
	return false;
}

bool Client::Disconnect()
{
	if (!connected)
		return false;

	sf::Packet p;
	StampPacket(PacketType::Disconnect, p);
	sf::Socket::Status s = socket.send(p, serverIP, serverPort);
	connected = false;
	socket.unbind();
	if (s != sf::Socket::Done)
		return false;

	return true;
}

void Client::Setup(void(*handler)(const PacketID &, sf::Packet &, Client *))
{
	packetHandler = std::bind(handler, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

void Client::UnregisterPacketHandler()
{
	packetHandler = nullptr;
}

void Client::Update(const sf::Time & time)
{
	if (!connected)
		return;

	serverTime += time;
	if (serverTime.asMilliseconds() < 0)
	{
		serverTime -= sf::milliseconds(sf::Int32(Network::HighestTimestamp));
		lastHeartbeat = serverTime;
		return;
	}

	if (serverTime.asMilliseconds() - lastHeartbeat.asMilliseconds() >= sf::Int32(Network::ClientTimeout))
	{
		std::cout << "Server connection timed out!" << std::endl;
		Disconnect();
	}
}

bool Client::IsConnected() const
{
	return connected;
}

void Client::SetPlayerName(const std::string & name)
{
	playerName = name;
}

sf::Mutex& Client::GetMutex()
{
	return mutex;
}

void Client::Listen()
{
	sf::Packet packet;
	sf::IpAddress recvIP;
	PortNumber recvPort;

	while (connected)
	{
		packet.clear();
		sf::Socket::Status status = socket.receive(packet, recvIP, recvPort);

		if (status != sf::Socket::Done)
		{
			if (connected)
			{
				std::cout << "Failed receiving a packet from " << recvIP << ":" << recvPort << ". Status: " << status << std::endl;
				continue;
			}
			else
			{
				std::cout << "Socket unbound" << std::endl;
				break;
			}
		}

		if (recvIP != serverIP)
			continue;

		PacketID ID;
		if (!(packet >> ID))
			continue;

		PacketType id = (PacketType)ID;
		if (id < PacketType::Disconnect || id >= PacketType::OutOfBounds)
			continue;

		if (id == PacketType::Heartbeat)
		{
			sf::Packet p;
			StampPacket(PacketType::Heartbeat, p);
			if (socket.send(p, serverIP, serverPort) != sf::Socket::Done)
				std::cout << "Failed sending a heartbeat!" << std::endl;

			sf::Int32 timestamp;
			packet >> timestamp;
			SetTime(sf::milliseconds(timestamp));
			lastHeartbeat = serverTime;
		}
		else if (packetHandler)
			packetHandler((PacketID)id, packet, this);
	}
}

void Client::CommandProcess()
{
	while (IsConnected())
	{
		std::string str;
		std::getline(std::cin, str);
		if (str != "")
		{
			if (str == "!quit")
			{
				Disconnect();
				break;
			}
			sf::Packet p;
			StampPacket(PacketType::Message, p);
			p << str;
			Send(p);
		}


	}
}

bool Client::Send(sf::Packet & packet)
{
	if (!connected)
		return false;

	if (socket.send(packet, serverIP, serverPort) != sf::Socket::Done)
		return false;

	//std::cout << "Packet sent to: " << serverIP << ":" << serverPort << std::endl;
	return true;
}

const sf::Time & Client::GetTime() const
{
	return serverTime;
}

const sf::Time & Client::GetLastHeartbeat() const
{
	return lastHeartbeat;
}

void Client::SetTime(const sf::Time & time)
{
	serverTime = time;
}

void Client::SetServerInfo(const sf::IpAddress & ip, const PortNumber & port)
{
	serverIP = ip;
	serverPort = port;
}
