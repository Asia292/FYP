#include "PickUp.h"

PickUp::PickUp(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, int mask) : Sensor(world, position, size)
{
	fixture = body->GetFixtureList();
	filter.maskBits = mask;
	fixture->SetFilterData(filter);

	//// SFML ////
	/*setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(0);
	if (mask == 0x0010)
		setFillColor(sf::Color::Black);
	else if (mask == 0x0100)
		setFillColor(sf::Color::White);*/
}

void PickUp::onAction(b2Body * other)
{
	del = true;
}

bool PickUp::getDel()
{
	return del;
}

PickUp::~PickUp()
{
	body->GetWorld()->DestroyBody(body);
}
