#include "HomeSensor.h"

HomeSensor::HomeSensor(b2World * world, const sf::Vector2f position, sf::Vector2f size, Player * play, TextureManager *texMan) : Sensor(world, position, size)
{
	player = play;

	texMan->setTexture("all", this);
	setSize(sf::Vector2f(0.01f, 0.01f));
	setPos(sf::Vector2f(position));

	if (player->getFilter().categoryBits == 0x0010)
		texMan->getFrames("lightDoor", this);
	else if (player->getFilter().categoryBits == 0x0100)
		texMan->getFrames("darkDoor", this);

	fade = false;
	a = 255;

	fixture = body->GetFixtureList();
	filter.maskBits = player->getFilter().categoryBits;
	fixture->SetFilterData(filter);
}

void HomeSensor::onAction(b2Body * other)
{
	fade = true;
}

void HomeSensor::offAction(b2Body * other)
{
	fade = false;
}

void HomeSensor::update(float timestep)
{
	Texture::update(timestep);

	if (fade && a != 0)
	{
		a -= 5;
	}
	else if (fade && a == 0)
	{
		player->setHome(true);
	}
	else if (!fade && a != 255)
	{
		player->setHome(false);
		a += 5;
	}

	currSprite.setColor(sf::Color(255, 255, 255, a));
}
