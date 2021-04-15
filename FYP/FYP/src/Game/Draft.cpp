#include "Draft.h"

Draft::Draft(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, const float orientation) : Sensor(world, position, size)
{
	angle = orientation;
	player = nullptr;
}

void Draft::onAction(b2Body * other)
{
	player = other;
}

void Draft::offAction(b2Body * other)
{
	player = nullptr;
}

void Draft::update(float timestep)
{
	if (player != nullptr)
	{
		b2Vec2 velo = player->GetLinearVelocity();

		if (angle == 0)
			velo.y = -2;
		else if (angle > 1.570 && angle < 1.571)
			velo.x = -2;
		else if (angle > 3.141 && angle < 3.142)
			velo.y = 2;
		else
			velo.x = 2;

		player->SetLinearVelocity(velo);
	}
}
