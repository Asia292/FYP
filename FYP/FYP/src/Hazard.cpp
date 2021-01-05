#include "Hazard.h"

Hazard::Hazard(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, const float orientation, int mask)
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

	setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(orientation);
	setFillColor(sf::Color::Blue);
	setOutlineThickness(0.f);


	fixture = body->GetFixtureList();
	filter.maskBits = mask;
	fixture->SetFilterData(filter);
}

void Hazard::setUserData(void * data)
{
	body->SetUserData(data);
}
