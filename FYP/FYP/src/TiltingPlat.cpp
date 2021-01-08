#include "TiltingPlat.h"

TiltingPlat::TiltingPlat(b2World * world, sf::Vector2f position, sf::Vector2f size, sf::Vector2f Anchor, float orientation, sf::Color colour)
{
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;

	shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	shape.m_radius = 0.0f;

	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	fixtureDef.shape = &shape;

	//// PLATFORM ////
	bodyDef.position.Set(position.x, position.y);
	bodyDef.angle = orientation;
	bodyDef.type = b2_dynamicBody;

	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
	body->SetAngularDamping(0.1f);

	//// ANCHOR ////
	bodyDef.type = b2_staticBody;

	b2CircleShape circ;
	circ.m_radius = fminf(size.x / 2.0f, size.y / 2.0f);
	fixtureDef.shape = &circ;

	anchor = world->CreateBody(&bodyDef);
	anchor->CreateFixture(&fixtureDef);

	//// JOINT ////
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = anchor;
	jointDef.bodyB = body;
	jointDef.collideConnected = false;
	jointDef.localAnchorA.Set(0.f, 0.f);// Centre of the box
	jointDef.localAnchorB.Set(Anchor.x, Anchor.y); // from constructor
	hinge = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

	//// SFML ////
	rectangle.setPosition(position);
	rectangle.setSize(size);
	rectangle.setOrigin(size * 0.5f);
	rectangle.setRotation(orientation);
	rectangle.setFillColor(colour);
	rectangle.setOutlineThickness(0.f);
}

void TiltingPlat::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(rectangle);
}

void TiltingPlat::update(float timestep)
{
	b2Vec2 pos = body->GetPosition();
	rectangle.setPosition(pos.x, pos.y);
	float angle = body->GetAngle() * 57.29577f;
	rectangle.setRotation(angle);
}

void TiltingPlat::setUserData(void * data)
{
	body->SetUserData(data);
	anchor->SetUserData(data);
}