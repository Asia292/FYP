#pragma once

#include "NetworkDefs.h"

#define HEARTBEAT_INTERVAL 1000 // Milliseconds 
#define HEARTBEAT_RETRIES 5
#define SERVER_PORT unsigned short(Network::ServerPort)
#define HIGHEST_TIMESTAMP sf::Int32(Network::HighestTimestamp)
#define CLIENT_TIMEOUT sf::Int32(Network::ClientTimeout)

struct ClientInfo
{
	sf::IpAddress clientIP;
	PortNumber clientPort;
	sf::Time lastHeartbeat;
	sf::Time heartbeatSent;
	bool heartbeatWaiting;
	unsigned short heartbeatRetry;
	unsigned int latency;

	ClientInfo(const sf::IpAddress& ip, const PortNumber& port, const sf::Time& heartbeat) : clientIP(ip), clientPort(port), lastHeartbeat(heartbeat), heartbeatWaiting(false), heartbeatRetry(0), latency(0) {}

	ClientInfo& operator = (const ClientInfo& rhs)
	{
		clientIP = rhs.clientIP;
		clientPort = rhs.clientPort;
		lastHeartbeat = rhs.lastHeartbeat;
		heartbeatSent = rhs.heartbeatSent;
		heartbeatWaiting = rhs.heartbeatWaiting;
		heartbeatRetry = rhs.heartbeatRetry;
		latency = rhs.latency;

		return *this;
	}
};

using Clients = std::unordered_map<ClientID, ClientInfo>;
class Server;
using SPacketHandler = std::function<void(sf::IpAddress&, const PortNumber&, const PacketID&, sf::Packet&, Server*)>;
using TimeoutHandler = std::function<void(const ClientID&)>;

class Server
{
private:
	void Setup();
	ClientID lastID;

	sf::UdpSocket incoming;
	sf::UdpSocket outgoing;

	SPacketHandler packetHandler;
	TimeoutHandler timeoutHandler;

	Clients clients;
	sf::Time serverTime;

	bool running;

	sf::Thread listenThread;
	sf::Mutex mutex;

	size_t totalSent;
	size_t totalRecieved;

public:
	template <class T>
	Server(void(T::*handler)(sf::IpAddress&, const PortNumber&, const PacketID&, sf::Packet&, Server*), T* instace) : listenThread(&Server::Listen, this)
	{
		packetHandler = std::bind(handler, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5);
	}

	Server(void(*handler)(sf::IpAddress&, const PortNumber&, const PacketID&, sf::Packet&, Server*));
	~Server();

	template <class T>
	void BindTimeoutHandler(void(T::*handler)(const ClientID&), T* instance)
	{
		timeoutHandler = std::bind(handler, instance, std::placeholders::_1);
	}

	void BindTimeoutHandler(void(*handler)(const ClientID&));
	bool Send(const ClientID& id, sf::Packet& packet);
	bool Send(sf::IpAddress& ip, const PortNumber& port, sf::Packet& packet);
	void Broadcast(sf::Packet& packet, const ClientID& ignore = ClientID(Network::NullID));
	void Listen();
	void Update(const sf::Time& time);

	ClientID AddClient(const sf::IpAddress& ip, const PortNumber& port);
	ClientID GetClientID(const sf::IpAddress& ip, const PortNumber& port);
	bool HasClient(const ClientID& id);
	bool HasClient(const sf::IpAddress& ip, const PortNumber& port);
	bool GetClientInfo(const ClientID& id, ClientInfo& info);
	bool RemoveClient(const ClientID& id);
	bool RemoveClient(const sf::IpAddress& ip, const PortNumber& port);

	void DisconnectAll();
	bool Start();
	bool Stop();
	bool IsRunning();

	unsigned int GetClientCount();
	std::string GetClientList();

	sf::Mutex& GetMutex();
};