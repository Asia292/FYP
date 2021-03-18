#pragma once
#include <gmock/gmock.h>
#include "..\..\Server\Server\include\ServerBase.h"

class ServerMock : public ServerBase
{
public:
	MOCK_METHOD(void, BindTimeoutHandler, (void(*handler)(const ClientID&)), (override));
	MOCK_METHOD(bool, Send, (const ClientID& id, sf::Packet& packet), (override));
	MOCK_METHOD(bool, Send, (sf::IpAddress& ip, const PortNumber& port, sf::Packet& packet), (override));
	MOCK_METHOD(void, Broadcast, (sf::Packet& packet, const ClientID& ignore), (override));
	MOCK_METHOD(void, Listen, (), (override));
	MOCK_METHOD(void, Update, (const sf::Time& time), (override));

	MOCK_METHOD(ClientID, AddClient, (const sf::IpAddress& ip, const PortNumber& port), (override));
	MOCK_METHOD(ClientID, GetClientID, (const sf::IpAddress& ip, const PortNumber& port), (override));
	MOCK_METHOD(bool, HasClient, (const ClientID& id), (override));
	MOCK_METHOD(bool, HasClient, (const sf::IpAddress& ip, const PortNumber& port), (override));
	MOCK_METHOD(bool, GetClientInfo, (const ClientID& id, ClientInfo& info), (override));
	MOCK_METHOD(bool, RemoveClient, (const ClientID& id), (override));
	MOCK_METHOD(bool, RemoveClient, (const sf::IpAddress& ip, const PortNumber& port), (override));

	MOCK_METHOD(void, DisconnectAll, (), (override));
	MOCK_METHOD(bool, Start, (), (override));
	MOCK_METHOD(bool, Stop, (), (override));
	MOCK_METHOD(bool, IsRunning, (), (override));

	MOCK_METHOD(unsigned int, GetClientCount, (), (override));
	MOCK_METHOD(std::string, GetClientList, (), (override));
	MOCK_METHOD(sf::Mutex&, GetMutex, (), (override));
};

