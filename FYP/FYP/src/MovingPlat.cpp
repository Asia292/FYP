#include "MovingPlat.h"

MovingPlat::MovingPlat(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, const float orientation, const sf::Vector2f &End)
{
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;

	bodyDef.position.Set(position.x, position.y);
	bodyDef.angle = orientation;
	bodyDef.type = b2_kinematicBody;

	body = world->CreateBody(&bodyDef);

	shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	shape.m_radius = 0.0f;

	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	fixtureDef.shape = &shape;

	body->CreateFixture(&fixtureDef);

	start = b2Vec2(position.x, position.y);
	end = b2Vec2(End.x, End.y);
	moveEnd = false;
	xMove = 0;
	yMove = 0;

	setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(orientation);
	setFillColor(sf::Color::Yellow);
	setOutlineThickness(0.f);
}

void MovingPlat::setUserData(void * data)
{
	body->SetUserData(data);
}

void MovingPlat::moveToEnd()
{
	if (end.x > start.x)
		xMove = -1;
	else if (end.x < start.x)
		xMove = 1;
	else
		xMove = 0;

	if (end.y > start.y)
		yMove = 1;
	else if (end.y < start.y)
		yMove = -1;
	else
		yMove = 0;

	moveEnd = true;
}

void MovingPlat::moveToStart()
{
	if (end.x > start.x)
		xMove = 1;
	else if (end.x < start.x)
		xMove = -1;
	else
		xMove = 0;

	if (end.y > start.y)
		yMove = -1;
	else if (end.y < start.y)
		yMove = 1;
	else
		yMove = 0;

	moveEnd = false;
}

void MovingPlat::update(float timestep)
{
	// Redo with reverce engineering velocity?
	if (moveEnd)
	{
		if ((body->GetPosition().x < end.x + 0.1) && (body->GetPosition().x > end.x - 0.1))
		{
			xMove = 0;

			if ((body->GetPosition().y < end.y + 0.1) && (body->GetPosition().y > end.y - 0.1))
				yMove = 0;
		}
	}
	else
	{
		if ((body->GetPosition().x < start.x + 0.1) && (body->GetPosition().x > start.x - 0.1))
		{
			xMove = 0;

			if ((body->GetPosition().y < start.y + 0.1) && (body->GetPosition().y > start.y - 0.1))
				yMove = 0;
		}
	}

	body->SetLinearVelocity(b2Vec2(xMove, yMove));

	b2Vec2 pos = body->GetPosition();
	setPosition(pos.x, pos.y);
}
