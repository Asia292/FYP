#include "Snapshot.h"

sf::Packet & operator<<(sf::Packet & l_packet, const Snapshot & snapshot)
{
	return l_packet << snapshot.type << snapshot.position.x << snapshot.position.y << snapshot.velocity.x << snapshot.velocity.y << snapshot.state << snapshot.direction;
}

sf::Packet & operator>>(sf::Packet & l_packet, Snapshot & snapshot)
{
	return l_packet >> snapshot.type >> snapshot.position.x >> snapshot.position.y >> snapshot.velocity.x >> snapshot.velocity.y >> snapshot.state >> snapshot.direction;
}

/*sf::Packet & operator<<(sf::Packet & l_packet, const sf::Keyboard::Key & key)
{
	return l_packet << key
}

sf::Packet & operator>>(sf::Packet & l_packet, sf::Keyboard::Key & key)
{
	return l_packet >> key;
}*/
