#pragma once

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

struct LevelSelectUpdate
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

struct LevelUpdate
{
	int object;
	int index;
	bool texture;
	int frame;
	float angle;
	sf::Vector2f position;
};

sf::Packet& operator <<(sf::Packet& l_packet, const LevelSelectUpdate& lvlUpdate);
sf::Packet& operator >>(sf::Packet& l_packet, LevelSelectUpdate& lvlUpdate);

sf::Packet& operator <<(sf::Packet& l_packet, const PlayerUpdate& playerUpdate);
sf::Packet& operator >>(sf::Packet& l_packet, PlayerUpdate& playerUpdate);

sf::Packet& operator <<(sf::Packet& l_packet, const LevelUpdate& lvlUpdate);
sf::Packet& operator >>(sf::Packet& l_packet, LevelUpdate& lvlUpdate);