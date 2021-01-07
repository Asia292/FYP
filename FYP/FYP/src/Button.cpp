#include "Button.h"

Button::Button(b2World * world, const sf::Vector2f & position, sf::Vector2f & size, DoorPlat * Door) : Sensor(world, position, size)
{
	door = Door;

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
}

void Button::offAction(b2Body * other)
{
	if (door != nullptr)
		door->close();
}
