#include "Client.h"
#include <SFML/Graphics.hpp>
#include "LevelSelect.h"

int r, g, b;

void HandlePacket(const PacketID& id, sf::Packet& packet, Client* client)
{
	if ((PacketType)id == PacketType::Message)
	{
		std::string message;
		packet >> message;
		std::cout << message << std::endl;
	}
	else if ((PacketType)id == PacketType::KeyPress)
	{
		int recieve;
		packet >> recieve;
		if (recieve == sf::Keyboard::Key::R)
		{
			r = 255;
			g = 0;
			b = 0;
		}
		else if (recieve == sf::Keyboard::Key::G)
		{
			r = 0;
			g = 255;
			b = 0;
		}
		else if (recieve == sf::Keyboard::Key::B)
		{
			r = 0;
			g = 0;
			b = 255;
		}
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
			if (str == "!quit")
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
	r = 120;
	g = 120;
	b = 120;
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
			sf::RenderWindow window(sf::VideoMode(1024, 800), "FYP"); // Open main window

			float fFrameTime = 1.f / 60.f;

			// Run a game loop
			while (window.isOpen())
			{
				sf::Event event;
				while (window.pollEvent(event))
				{
					// window closed button pressed
					if (event.type == sf::Event::Closed)
					{
						window.close();
						client.Disconnect();
					}
					if (event.type == sf::Event::KeyPressed)
					{
						auto key = event.key.code;

						sf::Packet p;
						StampPacket(PacketType::KeyPress, p);
						p << key;
						client.Send(p);
					}
				}

				// Find out how much time has elapsed
				float m_fElapsedTime = clock.getElapsedTime().asSeconds();
				// If a frame has past the update the physics
				if (m_fElapsedTime > fFrameTime)
				{
					clock.restart();
				}

				window.clear(sf::Color(r, g, b));

				window.display();

				client.Update(clock.restart());
			}
		}
	}
	else
		std::cout << "Failed to connect." << std::endl;

	std::cout << "Quitting..." << std::endl;
	sf::sleep(sf::seconds(1.f));

	

}