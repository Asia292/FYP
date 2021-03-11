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

struct LevelUpdate
{
	int currLevel;
	int back;
};

struct PlayerUpdate
{
	int player;
	int texture;
	int frame;
	bool flip;
	bool dead;
	sf::Vector2f position;
};

sf::Packet& operator <<(sf::Packet& l_packet, const Snapshot& snapshot);
sf::Packet& operator >>(sf::Packet& l_packet, Snapshot& snapshot);

sf::Packet& operator <<(sf::Packet& l_packet, const LevelUpdate& lvlUpdate);
sf::Packet& operator >>(sf::Packet& l_packet, LevelUpdate& lvlUpdate);

sf::Packet& operator <<(sf::Packet& l_packet, const PlayerUpdate& playerUpdate);
sf::Packet& operator >>(sf::Packet& l_packet, PlayerUpdate& playerUpdate);