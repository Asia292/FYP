#include "HomeSensor.h"

HomeSensor::HomeSensor(b2World * world, const sf::Vector2f& position, sf::Vector2f& size, Player * play) : Sensor(world, position, size)
{
	player = play;
}

void HomeSensor::onAction(b2Body * other)
{
	player->setHome(true);
}

void HomeSensor::offAction(b2Body * other)
{
	player->setHome(false);
}