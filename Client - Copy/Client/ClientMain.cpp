#include "Client.h"

void HandlePacket(const PacketID& id, sf::Packet& packet, Client* client)
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

void CommandProcess(Client* client)
{
	while (client->IsConnected())
	{
		std::string str;
		std::getline(std::cin, str);
		if (str != "")
		{
			if (str != "!quit")
			{
				client->Disconnect();
				break;
			}
			sf::Packet p;
			StampPacket(PacketType::Message, p);
			p << str;
			client->Send(p);
		}
	}
}

void main(int argc, char** argv)
{
	sf::IpAddress ip;
	PortNumber port;
	if (argc == 1)
	{
		std::cout << "Enter server IP: ";
		std::cin >> ip;
		std::cout << "Enter server port: ";
		std::cin >> port;
	}
	else if (argc == 3)
	{
		ip = argv[1];
		port = atoi(argv[2]);
	}
	else
		return;

	Client client;
	client.SetServerInfo(ip, port);
	client.Setup(&HandlePacket);
	sf::Thread c(&CommandProcess, &client);
	if (client.Connect())
	{
		c.launch();
		sf::Clock clock;
		clock.restart();
		while (client.IsConnected())
		{
			client.Update(clock.restart());
		}
	}
	else
		std::cout << "Failed to connect." << std::endl;

	std::cout << "Quitting..." << std::endl;
	sf::sleep(sf::seconds(1.f));
}