/*!
\file Sensor.cpp
*/

#include "Sensor.h"

Sensor::Sensor(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size)
{
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;


	bodyDef.position.Set(position.x, position.y);
	bodyDef.angle = 0;

	body = world->CreateBody(&bodyDef);

	shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	shape.m_radius = 0.0f;

	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	fixtureDef.shape = &shape;

	fixtureDef.isSensor = true; //Make it a sensor

	body->CreateFixture(&fixtureDef);
}

void Sensor::setUserData(void *data)
{
	body->SetUserData(data);
}