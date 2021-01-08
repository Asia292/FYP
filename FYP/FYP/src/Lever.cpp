#include "..\include\Lever.h"

Lever::Lever(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, DoorPlat * Door, bool Right) : Sensor(world, position, size)
{
	door = Door;
	platform = nullptr;
	pos = position;
	right = Right;

	setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(0);
	setFillColor(sf::Color(76, 76, 76, 255));
}

Lever::Lever(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, MovingPlat * plat, bool Right) : Sensor(world, position, size)
{
	platform = plat;
	door = nullptr;
	pos = position;
	right = Right;

	setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(0);
	setFillColor(sf::Color(76, 76, 76, 255));
}

void Lever::onAction(b2Body * other)
{
	if (right)
	{
		if (other->GetPosition().x > pos.x)
		{
			if (door != nullptr)
				door->open();
			if (platform != nullptr)
				platform->moveToEnd();
		}
		else if (other->GetPosition().x < pos.x)
		{
			if (door != nullptr)
				door->close();
			if (platform != nullptr)
				platform->moveToStart();
		}
	}
	else
	{
		if (other->GetPosition().x < pos.x)
		{
			if (door != nullptr)
				door->open();
			if (platform != nullptr)
				platform->moveToEnd();
		}
		else if (other->GetPosition().x > pos.x)
		{
			if (door != nullptr)
				door->close();
			if (platform != nullptr)
				platform->moveToStart();
		}
	}
}
