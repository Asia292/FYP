#include "Block.h"

Block::Block(b2World * world, const sf::Vector2f & position, const sf::Vector2f & size, const float orientation, TextureManager *texMan)
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
	body->SetFixedRotation(false);

	texMan->setTexture("all", this);
	texMan->getFrames("Block", this);
	setSize(sf::Vector2f(0.0075f, 0.0075f));

	/*setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(orientation);
	setFillColor(sf::Color(96, 96, 96, 255));
	setOutlineThickness(0.f);*/
}

void Block::update(float timestep)
{
	Texture::update(timestep);
	b2Vec2 pos = body->GetPosition();
	currSprite.setPosition(pos.x, pos.y); 
	float angle = body->GetAngle() * 57.29577f;
	currSprite.setRotation(angle);
}

void Block::setUserData(void * data)
{
	body->SetUserData(data);
}