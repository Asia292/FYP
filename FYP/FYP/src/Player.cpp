#include "Player.h"

Player::Player(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, const float orientation, int cat, sf::Color col)
{
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;

	bodyDef.position.Set(position.x, position.y);
	bodyDef.angle = orientation;
	bodyDef.type = b2_dynamicBody;

	body = world->CreateBody(&bodyDef);

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
	setFillColor(col);
	setOutlineThickness(0.f);


	fixture = body->GetFixtureList();
	filter.categoryBits = cat;
	filter.maskBits = 0x0001;
	fixture->SetFilterData(filter);

	grounded = false;
	dead = false;
	home = false;
}

void Player::update(float timestep)
{
	b2Vec2 pos = body->GetPosition();
	setPosition(pos.x, pos.y);
}

void Player::setUserData(void * data)
{
	body->SetUserData(data);
}

void Player::moveLeft()
{
	b2Vec2 velo = body->GetLinearVelocity();
	velo.x = -3;
	body->SetLinearVelocity(velo);
}

void Player::moveRight()
{
	b2Vec2 velo = body->GetLinearVelocity();
	velo.x = 3;
	body->SetLinearVelocity(velo);
}

void Player::jump()
{
	if (grounded)
	{
		b2Vec2 velo = body->GetLinearVelocity();
		velo.y = -4.5;
		body->SetLinearVelocity(velo);
	}
}

void Player::idle()
{
	b2Vec2 velo = body->GetLinearVelocity();
	velo.x = 0;
	body->SetLinearVelocity(velo);
}

void Player::setGrounded(bool ground)
{
	grounded = ground;
}

void Player::setHome(bool Home)
{
	home = Home;
}

bool Player::getHome()
{
	return home;
}

void Player::setDead(bool Dead)
{
	dead = Dead;
}

bool Player::getDead()
{
	return dead;
}
