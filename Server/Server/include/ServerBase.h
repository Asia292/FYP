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
class ServerBase;
using SPacketHandler = std::function<void(sf::IpAddress&, const PortNumber&, const PacketID&, sf::Packet&, ServerBase*)>;
using TimeoutHandler = std::function<void(const ClientID&)>;

class ServerBase
{
public:
	virtual ~ServerBase() = default;

	virtual void BindTimeoutHandler(void(*handler)(const ClientID&)) = 0;
	virtual bool Send(const ClientID& id, sf::Packet& packet) = 0;
	virtual bool Send(sf::IpAddress& ip, const PortNumber& port, sf::Packet& packet) = 0;
	virtual void Broadcast(sf::Packet& packet, const ClientID& ignore = ClientID(Network::NullID)) = 0;
	virtual void Listen() = 0;
	virtual void Update(const sf::Time& time) = 0;

	virtual ClientID AddClient(const sf::IpAddress& ip, const PortNumber& port) = 0;
	virtual ClientID GetClientID(const sf::IpAddress& ip, const PortNumber& port) = 0;
	virtual bool HasClient(const ClientID& id) = 0;
	virtual bool HasClient(const sf::IpAddress& ip, const PortNumber& port) = 0;
	virtual bool GetClientInfo(const ClientID& id, ClientInfo& info) = 0;
	virtual bool RemoveClient(const ClientID& id) = 0;
	virtual bool RemoveClient(const sf::IpAddress& ip, const PortNumber& port) = 0;

	virtual void DisconnectAll() = 0;
	virtual bool Start() = 0;
	virtual bool Stop() = 0;
	virtual bool IsRunning() = 0;

	virtual unsigned int GetClientCount() = 0;
	virtual std::string GetClientList() = 0;

	virtual sf::Mutex& GetMutex() = 0;
};