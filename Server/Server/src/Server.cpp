#include "Server.h"

void Server::Setup()
{
	lastID = 0;
	running = false;
	totalSent = 0;
	totalRecieved = 0;
}

Server::Server(void(*handler)(sf::IpAddress &, const PortNumber &, const PacketID &, sf::Packet &, Server *)) : listenThread(&Server::Listen, this)
{
	packetHandler = std::bind(handler, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5);
}

Server::~Server()
{
	Stop();
}

void Server::BindTimeoutHandler(void(*handler)(const ClientID &))
{
	timeoutHandler = std::bind(handler, std::placeholders::_1);
}

bool Server::Send(const ClientID & id, sf::Packet & packet)
{
	sf::Lock lock(mutex);

	auto itr = clients.find(id);

	if (itr == clients.end())
		return false;

	if (outgoing.send(packet, itr->second.clientIP, itr->second.clientPort) != sf::Socket::Done)
	{
		std::cout << "Error sending a packet..." << std::endl;
		return false;
	}

	totalSent += packet.getDataSize();

	return true;
}

bool Server::Send(sf::IpAddress & ip, const PortNumber & port, sf::Packet & packet)
{
	if (outgoing.send(packet, ip, port) != sf::Socket::Done)
		return false;

	totalSent += packet.getDataSize();
	return true;
}

void Server::Broadcast(sf::Packet & packet, const ClientID & ignore)
{
	sf::Lock lock(mutex);

	for (auto &itr : clients)
	{
		//if (itr.first != ignore)
		//{
			if (outgoing.send(packet, itr.second.clientIP, itr.second.clientPort) != sf::Socket::Done)
			{
				std::cout << "Error broadcasting a packet to client: " << itr.first << std::endl;
				continue;
			}

			totalSent += packet.getDataSize();
		//}
	}
}

void Server::Listen()
{
	sf::IpAddress ip;
	PortNumber port;
	sf::Packet packet;

	while (running)
	{
		packet.clear();

		sf::Socket::Status status = incoming.receive(packet, ip, port);

		if (status != sf::Socket::Done)
		{
			if(running)
			{
				std::cout << "Error receiving a packet from: " << ip << ":" << port << ". Code: " << status << std::endl;
				continue;
			}
			else
			{
				std::cout << "Socket unbound." << std::endl;
				break;
			}
		}

		totalRecieved += packet.getDataSize();

		//std::cout << "Packet: " << packet << " : " << packet.getDataSize() << std::endl;

		PacketID p_id;
		if (!(packet >> p_id))
		{
			//std::cout << "Here" << std::endl;
			continue;
		}
		//std::cout << "ID: " << std::to_string(p_id) << std::endl;

		PacketType id = (PacketType)p_id;

		if (id < PacketType::Disconnect || id >= PacketType::OutOfBounds)
			continue;

		if (id == PacketType::Heartbeat)
		{
			sf::Lock lock(mutex);

			for (auto &itr : clients)
			{
				if (itr.second.clientIP != ip || itr.second.clientPort != port)
					continue;

				if (!itr.second.heartbeatWaiting)
				{
					std::cout << "Invalid heartbeat packet recieved!" << std::endl;
					break;
				}
				itr.second.latency = serverTime.asMilliseconds() - itr.second.heartbeatSent.asMilliseconds();
				itr.second.lastHeartbeat = serverTime;
				itr.second.heartbeatWaiting = false;
				itr.second.heartbeatRetry = 0;
				break;
			}
		}
		else if(packetHandler)
		{ 
			//std::cout << "Packet handler" << std::endl;
			packetHandler(ip, port, (PacketID)id, packet, this);
		}
	}
}

void Server::Update(const sf::Time & time)
{
	serverTime += time;

	if (serverTime.asMilliseconds() < 0)
	{
		serverTime -= sf::milliseconds(HIGHEST_TIMESTAMP);
		sf::Lock lock(mutex);
		for (auto& itr : clients)
		{
			itr.second.lastHeartbeat = sf::milliseconds(std::abs(itr.second.lastHeartbeat.asMilliseconds() - HIGHEST_TIMESTAMP));
		}
	}

	sf::Lock lock(mutex);

	for (auto itr = clients.begin(); itr != clients.end();)
	{
		sf::Int32 elapsed = serverTime.asMilliseconds() - itr->second.lastHeartbeat.asMilliseconds();

		if (elapsed >= HEARTBEAT_INTERVAL)
		{
			if (elapsed >= CLIENT_TIMEOUT || itr->second.heartbeatRetry > HEARTBEAT_RETRIES)
			{
				std::cout << "Client " << itr->first << "has timed out." << std::endl;

				if (timeoutHandler)
					timeoutHandler(itr->first);

				itr = clients.erase(itr);
				continue;
			}

			if (!itr->second.heartbeatWaiting || (elapsed >= HEARTBEAT_INTERVAL * (itr->second.heartbeatRetry + 1)))
			{
				if (itr->second.heartbeatRetry >= 3)
					std::cout << "Re-try(" << itr->second.heartbeatRetry << ") heartbeat for client " << itr->first << std::endl;

				sf::Packet heartBeat;
				StampPacket(PacketType::Heartbeat, heartBeat);
				heartBeat << serverTime.asMilliseconds();
				Send(itr->first, heartBeat);

				if (itr->second.heartbeatRetry == 0)
					itr->second.heartbeatSent = serverTime;

				itr->second.heartbeatWaiting = true;
				++itr->second.heartbeatRetry;

				totalSent += heartBeat.getDataSize();
			}
		}
		itr++;
	}
}

ClientID Server::AddClient(const sf::IpAddress & ip, const PortNumber & port)
{
	sf::Lock lock(mutex);

	for (auto &itr : clients)
	{
		if (itr.second.clientIP == ip && itr.second.clientPort == port)
			return ClientID(Network::NullID);
	}

	ClientID id = lastID;
	ClientInfo info(ip, port, serverTime);
	clients.insert(std::make_pair(id, info));
	lastID++;
	return id;
}

ClientID Server::GetClientID(const sf::IpAddress & ip, const PortNumber & port)
{
	sf::Lock lock(mutex);

	for (auto &itr : clients)
	{
		if (itr.second.clientIP == ip && itr.second.clientPort == port)
			return itr.first;
	}

	return ClientID(Network::NullID);
}

bool Server::HasClient(const ClientID& id)
{
	return (clients.find(id) != clients.end());
}

bool Server::HasClient(const sf::IpAddress & ip, const PortNumber & port)
{
	return (GetClientID(ip, port) >= 0);
}

bool Server::GetClientInfo(const ClientID & id, ClientInfo & info)
{
	sf::Lock lock(mutex);

	for (auto& itr : clients)
	{
		if (itr.first == id)
		{
			info = itr.second;
			return true;
		}
	}

	return false;
}

bool Server::RemoveClient(const ClientID & id)
{
	sf::Lock lock(mutex);

	auto itr = clients.find(id);

	if (itr == clients.end())
		return false;

	sf::Packet p;
	StampPacket(PacketType::Disconnect, p);
	Send(id, p);
	clients.erase(itr);
	return true;
}

bool Server::RemoveClient(const sf::IpAddress & ip, const PortNumber& port)
{
	sf::Lock lock(mutex);

	for (auto itr = clients.begin(); itr != clients.end(); itr++)
	{
		if (itr->second.clientIP == ip && itr->second.clientPort == port)
		{
			sf::Packet p;
			StampPacket(PacketType::Disconnect, p);
			Send(itr->first, p);
			clients.erase(itr);
			return true;
		}
	}
	return false;
}

void Server::DisconnectAll()
{
	if (!running)
		return;

	sf::Packet p;
	StampPacket(PacketType::Disconnect, p);
	Broadcast(p);
	sf::Lock lock(mutex);
	clients.clear();
}

bool Server::Start()
{
	if (running)
		return false;

	if (incoming.bind(SERVER_PORT) != sf::Socket::Done)
		return false;

	outgoing.bind(sf::Socket::AnyPort);
	Setup();
	std::cout << "Incoming port: " << incoming.getLocalPort() << ". Outgoing port: " << outgoing.getLocalPort() << std::endl;
	listenThread.launch();
	running = true;
	return true;
}

bool Server::Stop()
{
	if (!running)
		return false;

	DisconnectAll();
	running = false;
	incoming.unbind();
	return true;
}

bool Server::IsRunning()
{
	return running;
}

unsigned int Server::GetClientCount()
{
	return clients.size();
}

std::string Server::GetClientList()
{
	std::string list;

	for (auto& x : clients)
	{
		list += "ID: ", std::to_string(x.first), " Port: ", std::to_string(x.second.clientPort), "/n";
	}

	return list;
}

sf::Mutex & Server::GetMutex()
{
	return mutex;
}
