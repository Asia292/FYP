#include "Overloads.h"

sf::Packet & operator<<(sf::Packet & l_packet, const LevelSelectUpdate & lvlUpdate)
{
	return l_packet << lvlUpdate.currLevel << lvlUpdate.back;
}

sf::Packet & operator>>(sf::Packet & l_packet, LevelSelectUpdate & lvlUpdate)
{
	return l_packet >> lvlUpdate.currLevel >> lvlUpdate.back;
}

sf::Packet & operator<<(sf::Packet & l_packet, const PlayerUpdate & playerUpdate)
{
	return l_packet << playerUpdate.player << playerUpdate.texture << playerUpdate.frame << playerUpdate.flip << playerUpdate.dead << playerUpdate.position.x << playerUpdate.position.y;
}

sf::Packet & operator>>(sf::Packet & l_packet, PlayerUpdate & playerUpdate)
{
	return l_packet >> playerUpdate.player >> playerUpdate.texture >> playerUpdate.frame >> playerUpdate.flip >> playerUpdate.dead >> playerUpdate.position.x >> playerUpdate.position.y;
}

sf::Packet & operator<<(sf::Packet & l_packet, const LevelUpdate & lvlUpdate)
{
	return l_packet << lvlUpdate.object << lvlUpdate.index << lvlUpdate.texture << lvlUpdate.frame << lvlUpdate.angle << lvlUpdate.position.x << lvlUpdate.position.y;
}

sf::Packet & operator>>(sf::Packet & l_packet, LevelUpdate & lvlUpdate)
{
	return l_packet >> lvlUpdate.object >> lvlUpdate.index >> lvlUpdate.texture >> lvlUpdate.frame >> lvlUpdate.angle >> lvlUpdate.position.x >> lvlUpdate.position.y;
}

