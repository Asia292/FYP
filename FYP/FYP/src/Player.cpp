#include "Player.h"

Player::Player(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, const float orientation, int cat, TextureManager *texMan)
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

	/*setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(orientation);
	setFillColor(col);
	setOutlineThickness(0.f);*/


	fixture = body->GetFixtureList();
	filter.categoryBits = cat;
	filter.maskBits = 0x0001;
	fixture->SetFilterData(filter);

	texMan->setTexture("characters", this);
	setLoop(false);
	setPos(sf::Vector2f(position.x, position.y - 0.1f));
	setAnim();

	if (cat == 0x0010)
	{
		texMan->getFrames("lightIdle", this);
		setSize(sf::Vector2f(0.00275f, 0.00275f));
	}
	else if (cat == 0x0100)
	{
		texMan->getFrames("darkIdle", this);
		setSize(sf::Vector2f(0.003f, 0.003f));
	}

	grounded = false;
	dead = false;
	home = false;
	player = cat;
	texture = texMan;
	run = false;
}

void Player::update(float timestep)
{
	Texture::update(timestep);
	currSprite.setScale(sf::Vector2f(0.00275 - (int)flip * 0.0055, 0.00275f));	// 1 - (int)flip * 2
	b2Vec2 pos = body->GetPosition();
	if (player == 0x0010)
		currSprite.setPosition(pos.x, pos.y - 0.3f);
	else if (player == 0x0100)
		currSprite.setPosition(pos.x, pos.y - 0.1f);
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

	if (!run && grounded)
	{
		run = true;
		setFrame(0);

		if (player == 0x0010)
			texture->getFrames("lightRun", this);
		else if (player == 0x0100)
			texture->getFrames("darkRun", this);

		setLoop(true);
	}
	setFlip(true);
}

void Player::moveRight()
{
	b2Vec2 velo = body->GetLinearVelocity();
	velo.x = 3;
	body->SetLinearVelocity(velo);

	if (!run && grounded)
	{
		run = true;
		setFrame(0);

		if (player == 0x0010)
			texture->getFrames("lightRun", this);
		else if (player == 0x0100)
			texture->getFrames("darkRun", this);

		setLoop(true);
	}
	setFlip(false);
}

void Player::jump()
{
	if (grounded)
	{
		b2Vec2 velo = body->GetLinearVelocity();
		velo.y = -4.5;
		body->SetLinearVelocity(velo);

		setFrame(0);

		if (player == 0x0010)
			texture->getFrames("lightJump", this);
		else if (player == 0x0100)
			texture->getFrames("darkJump", this);

		setLoop(false);
	}
}

void Player::idle()
{
	b2Vec2 velo = body->GetLinearVelocity();
	velo.x = 0;
	body->SetLinearVelocity(velo);

	setFrame(0);

	if (player == 0x0010)
		texture->getFrames("lightIdle", this);
	else if (player == 0x0100)
		texture->getFrames("darkIdle", this);

	setLoop(false);
	run = false;
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
