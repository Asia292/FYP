/*!
\file Button.cpp
*/

#include "Button.h"

Button::Button(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, DoorPlat * Door, TextureManager *texMan, const std::string col) : Sensor(world, position, size)
{
	door = Door;
	platform = nullptr;

	texMan->setTexture("all", this);
	texMan->getFrames(col, this);
	setSize(sf::Vector2f(0.01f, 0.01f));
	setPos(sf::Vector2f(position));

	/*setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(0);
	setFillColor(sf::Color(76, 76, 76, 255));*/
}

Button::Button(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, MovingPlat * plat, TextureManager *texMan, const std::string col) : Sensor(world, position, size)
{
	platform = plat;
	door = nullptr;

	texMan->setTexture("all", this);
	texMan->getFrames(col, this);
	setSize(sf::Vector2f(0.01f, 0.01f));
	setPos(sf::Vector2f(position));

	/*setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(0);
	setFillColor(sf::Color(76, 76, 76, 255));*/
}

void Button::onAction(b2Body * other)
{
	if (door != nullptr)
		door->open();
	if (platform != nullptr)
		platform->moveToEnd();
}

void Button::offAction(b2Body * other)
{
	if (door != nullptr)
		door->close();
	if (platform != nullptr)
		platform->moveToStart();
}

void Button::update(float timestep)
{
	Texture::update(timestep);
}
