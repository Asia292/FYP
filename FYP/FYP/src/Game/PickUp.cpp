/*!
\file PickUp.cpp
*/

#include "PickUp.h"

PickUp::PickUp(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, int mask, TextureManager *texMan) : Sensor(world, position, size)
{
	fixture = body->GetFixtureList();
	filter.maskBits = mask;
	fixture->SetFilterData(filter);

	texMan->setTexture("all", this);
	setSize(sf::Vector2f(0.0075f, 0.0075f));
	setPos(sf::Vector2f(position));

	if (mask == 0x0100)
		texMan->getFrames("lightPickUp", this);
	else if (mask == 0x0010)
		texMan->getFrames("darkPickUp", this);

	del = false;

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

void PickUp::update(float timestep)
{
	Texture::update(timestep);
}

bool PickUp::getDel()
{
	return del;
}

PickUp::~PickUp()
{
	body->GetWorld()->DestroyBody(body);
}
