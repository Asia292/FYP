#pragma once

#include <Windows.h>
#include "NetworkDefs.h"

#define CONNECT_TIMEOUT 10000 //milliseconds

class Client;
using CPacketHandler = std::function<void(const PacketID&, sf::Packet&, Client*)>;

class Client
{
private:
	std::string playerName;

	sf::UdpSocket socket;
	sf::IpAddress serverIP;
	PortNumber serverPort;
	CPacketHandler packetHandler;
	bool connected = false;
	sf::Time serverTime;
	sf::Time lastHeartbeat;

	sf::Thread listenThread;
	sf::Thread commandThread;
	sf::Mutex mutex;

public:
	Client();
	~Client();
	bool Connect();
	bool Disconnect();
	void Listen();
	void CommandProcess();
	bool Send(sf::Packet& packet);
	const sf::Time& GetTime() const;
	const sf::Time& GetLastHeartbeat() const;
	void SetTime(const sf::Time& time);
	void SetServerInfo(const sf::IpAddress& ip, const PortNumber& port);

	template<class T>
	void Setup(void(T::*handler)(const PacketID&, sf::Packet&, Client*), T* instance)
	{
		packetHandler = std::bind(handler, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	}

	void Setup(void(*handler)(const PacketID&, sf::Packet&, Client*));
	void UnregisterPacketHandler();
	void Update(const sf::Time& time);
	bool IsConnected() const;
	void SetPlayerName(const std::string& name);
	sf::Mutex& GetMutex();
};