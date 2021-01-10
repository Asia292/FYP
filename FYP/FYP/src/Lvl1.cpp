#include "Lvl1.h"

Lvl1::Lvl1(TextureManager * textMan, b2World * world)
{
	textMan->setTexture("lvl1", this);
	setBg();
}

Lvl1::~Lvl1()
{
}

void Lvl1::update(float timestep)
{
	Texture::update(timestep);
}

void Lvl1::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(currSprite, states);
}
