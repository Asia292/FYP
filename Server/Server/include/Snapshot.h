#pragma once

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

struct Snapshot
{
	std::string type;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Uint8 state;
	sf::Uint8 direction;
};

sf::Packet& operator <<(sf::Packet& l_packet, const Snapshot& snapshot);
sf::Packet& operator >>(sf::Packet& l_packet, Snapshot& snapshot);

/*sf::Packet& operator <<(sf::Packet& l_packet, const sf::Keyboard::Key& key);
sf::Packet& operator >>(sf::Packet& l_packet, sf::Keyboard::Key& key);*/