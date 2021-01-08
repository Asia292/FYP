#include "Button.h"

Button::Button(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, DoorPlat * Door) : Sensor(world, position, size)
{
	door = Door;
	platform = nullptr;

	setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(0);
	setFillColor(sf::Color(76, 76, 76, 255));
}

Button::Button(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, MovingPlat * plat) : Sensor(world, position, size)
{
	platform = plat;
	door = nullptr;

	setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(0);
	setFillColor(sf::Color(76, 76, 76, 255));
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
