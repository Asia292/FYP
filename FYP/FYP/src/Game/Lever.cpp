/*!
\file Lever.cpp
*/

#include "Lever.h"

Lever::Lever(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, DoorPlat * Door, bool Right, TextureManager *texMan, const std::string col, const std::string back) : Sensor(world, position, size)
{
	door = Door;
	platform = nullptr;
	pos = position;
	right = Right;
	flipped = false;
	revTex = false;

	texture = texMan;
	forward = col;
	reverse = back;

	texMan->setTexture("all", this);
	texMan->getFrames(reverse, this);
	if (!right)
		flip = true;

	setSize(sf::Vector2f(0.01f * (1 - (int)flip * 2), 0.01f));
	setLoop(false);
	setPos(sf::Vector2f(position));
	setAnim();
	setFrame(2);

	/*setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(0);
	setFillColor(sf::Color(76, 76, 76, 255));*/
}

Lever::Lever(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, MovingPlat * plat, bool Right, TextureManager *texMan, const std::string col, const std::string back) : Sensor(world, position, size)
{
	platform = plat;
	door = nullptr;
	pos = position;
	right = Right;
	flipped = false;

	texture = texMan;
	forward = col;
	reverse = back;

	texMan->setTexture("all", this);
	texMan->getFrames(reverse, this);
	if (!right)
		flip = true;

	setSize(sf::Vector2f(0.01f * (1 - (int)flip * 2), 0.01f));
	setLoop(false);
	setPos(sf::Vector2f(position));
	setAnim();
	setFrame(2);

	/*setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(0);
	setFillColor(sf::Color(76, 76, 76, 255));*/
}

void Lever::onAction(b2Body * other)
{
	if (right)
	{
		if (other->GetPosition().x > pos.x)
		{
			if (!flipped)
			{
				setFrame(0);
				texture->getFrames(forward, this);

				flipped = true;
				revTex = false;
			}

			if (door != nullptr)
				door->open();
			if (platform != nullptr)
				platform->moveToEnd();
		}
		else if (other->GetPosition().x < pos.x)
		{
			if (flipped)
			{
				setFrame(0);
				texture->getFrames(reverse, this);

				flipped = false;
				revTex = true;
			}

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
			if (!flipped)
			{
				setFrame(0);
				texture->getFrames(forward, this);

				flipped = true;
				revTex = false;
			}

			if (door != nullptr)
				door->open();
			if (platform != nullptr)
				platform->moveToEnd();
		}
		else if (other->GetPosition().x > pos.x)
		{
			if (flipped)
			{
				setFrame(0);
				texture->getFrames(reverse, this);

				flipped = false;
				revTex = true;
			}

			if (door != nullptr)
				door->close();
			if (platform != nullptr)
				platform->moveToStart();
		}
	}
}

void Lever::update(float timestep)
{
	Texture::update(timestep);
}

void Lever::setTexture(bool tex)
{
	if (tex)
	{
		texture->getFrames(reverse, this);
		revTex = true;
	}
	else
	{
		texture->getFrames(forward, this);
		revTex = false;
	}
}
