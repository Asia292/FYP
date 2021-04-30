/*!
\file Floor.cpp
*/

#include "Floor.h"

Floor::Floor(const b2Vec2 *verts, int32 count, b2World * world)
{
	b2ChainShape shape;
	b2FixtureDef fixtureDef;
	b2BodyDef bodyDef;

	shape.CreateChain(verts, count);

	body = world->CreateBody(&bodyDef);

	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	fixtureDef.shape = &shape;

	body->CreateFixture(&shape, 1);
}

void Floor::setUserData(void *data)
{
	body->SetUserData(data);
}