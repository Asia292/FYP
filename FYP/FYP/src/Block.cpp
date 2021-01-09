#include "Block.h"

Block::Block(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, const float orientation)
{
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;

	bodyDef.position.Set(position.x, position.y);
	bodyDef.angle = orientation;
	bodyDef.type = b2_dynamicBody;

	body = world->CreateBody(&bodyDef);
	body->SetUserData(this);

	shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	shape.m_radius = 0.0f;

	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	fixtureDef.shape = &shape;

	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(true);

	setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(orientation);
	setFillColor(sf::Color(96, 96, 96, 255));
	setOutlineThickness(0.f);
}

void Block::update(float timestep)
{
	b2Vec2 pos = body->GetPosition();
	setPosition(pos.x, pos.y);
}

void Block::setUserData(void * data)
{
	body->SetUserData(data);
}
