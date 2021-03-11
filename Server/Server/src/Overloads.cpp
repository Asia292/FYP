#include "Overloads.h"

sf::Packet & operator<<(sf::Packet & l_packet, const Snapshot & snapshot)
{
	return l_packet << snapshot.type << snapshot.position.x << snapshot.position.y << snapshot.velocity.x << snapshot.velocity.y << snapshot.state << snapshot.direction;
}

sf::Packet & operator>>(sf::Packet & l_packet, Snapshot & snapshot)
{
	return l_packet >> snapshot.type >> snapshot.position.x >> snapshot.position.y >> snapshot.velocity.x >> snapshot.velocity.y >> snapshot.state >> snapshot.direction;
}

sf::Packet & operator<<(sf::Packet & l_packet, const LevelUpdate & lvlUpdate)
{
	return l_packet << lvlUpdate.currLevel << lvlUpdate.back;
}

sf::Packet & operator>>(sf::Packet & l_packet, LevelUpdate & lvlUpdate)
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

