/*!
\file DoorPlat.cpp
*/

#include "DoorPlat.h"

DoorPlat::DoorPlat(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size, const float orientation, bool close, TextureManager *texMan, const std::string plat, bool onClient)
{
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;

	bodyDef.position.Set(position.x, position.y);
	bodyDef.angle = orientation;

	door = world->CreateBody(&bodyDef);
	top = world->CreateBody(&bodyDef);

	shape.m_radius = 0.0f;

	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	fixtureDef.shape = &shape;

	//// DOOR ////1.47f, 0.26f 0.5,0.16
	shape.SetAsBox(size.x * 0.5f, size.y * 0.5f, b2Vec2(-0.75f, 0.f), 0.f);
	door->CreateFixture(&fixtureDef);
	platform = new Texture();

	fixture = door->GetFixtureList();
	filter.maskBits = 0x0110;
	fixture->SetFilterData(filter);

	//// ANCHOR/SIDE ////
	shape.SetAsBox(size.x * 0.5f, 0.04f * 0.5f, b2Vec2(-(size.x * 1.4f), -((size.y / 2) + 0.02)), 0.f);
	top->CreateFixture(&fixtureDef);
	fixture = top->GetFixtureList();
	filter.maskBits = 0x1000;
	fixture->SetFilterData(filter);
	shape.SetAsBox(size.x * 0.5f, 0.04f * 0.5f, b2Vec2(-(size.x * 1.4f), ((size.y / 2) + 0.02)), 0.f);
	top->CreateFixture(&fixtureDef);
	fixture = top->GetFixtureList();
	filter.maskBits = 0x1000;
	fixture->SetFilterData(filter);
	shape.SetAsBox(0.18f * 0.5f, size.y * 0.5f, b2Vec2(-(size.x * 1.9f), 0.f), 0.f);
	top->CreateFixture(&fixtureDef);

	fixture = top->GetFixtureList();
	filter.maskBits = 0x1000;
	fixture->SetFilterData(filter);
	
	//// JOINT ////
	door->SetType(b2BodyType::b2_dynamicBody);
	b2MotorJointDef jointDef;
	jointDef.Initialize(top, door);
	jointDef.maxForce = 1000.0f; // Force much large than we'd ever need
	jointDef.maxTorque = 1000.0f; // Avoid rotation with high torque
	motor = (b2MotorJoint*)world->CreateJoint(&jointDef);

	texMan->setTexture("all", platform);
	texMan->getFrames(plat, platform);
	if (orientation == 0 || (orientation > 3.141 && orientation < 3.142))
	{
		rot = false;
		platform->setPos(sf::Vector2f(door->GetFixtureList()->GetAABB(0).GetCenter().x, door->GetPosition().y));
	}
	else
	{
		rot = true;
		platform->setPos(sf::Vector2f(door->GetPosition().x, door->GetFixtureList()->GetAABB(0).GetCenter().y));
	}
	platform->setSize(sf::Vector2f(0.0075f * size.x, 0.01f));
	platform->setAngle(orientation * 57.29577f);


	//// SFML ////
	/*Top.setPosition(sf::Vector2f(top->GetPosition().x - 2.2f, top->GetPosition().y));
	Top.setSize(sf::Vector2f(1.5f, 0.3f));
	Top.setOrigin(Top.getSize() * 0.5f);
	Top.setFillColor(sf::Color(60, 60, 60));
	Top.setOutlineThickness(0.f);

	Door.setPosition(sf::Vector2f(door->GetFixtureList()->GetAABB(0).GetCenter().x, door->GetPosition().y));
	Door.setSize(sf::Vector2f(1.47f, 0.26f));
	Door.setOrigin(Door.getSize() * 0.5f);
	Door.setFillColor(sf::Color(90, 45, 0));
	Door.setOutlineThickness(0.f);*/
	

	mTime = 1.5f;
	if (close)
		state = CLOSED;
	else
	{
		state = OPEN;
		motor->SetLinearOffset(b2Vec2(-size.x, 0));
	}

	closed = close;
	length = size.x;
	client = onClient;
}

void DoorPlat::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	platform->draw(target, states);
}

void DoorPlat::setUserData(void *data)
{
	door->SetUserData(data);
	top->SetUserData(data);
}

void DoorPlat::update(float timestep)
{
	platform->update(timestep);

	if (state == OPENING)
	{
		eTime += timestep;

		float t = eTime / mTime;
		float dist;

		if (t < 1.0f)
			dist = t * -length;
		else
		{
			dist = -length;
			state = OPEN;
		}

		motor->SetLinearOffset(b2Vec2(dist, 0));
	}

	if (state == CLOSING)
	{
		eTime += timestep;

		float t = eTime / mTime;
		float dist;

		if (t < 1.0f)
			dist = (1.0f - t)*-length;
		else
		{
			dist = 0.0f;
			state = CLOSED;
		}

		motor->SetLinearOffset(b2Vec2(dist, 0));
	}

	if (!client)
	{
		if (!rot)
			platform->setPos(sf::Vector2f(door->GetFixtureList()->GetAABB(0).GetCenter().x, door->GetPosition().y));
		else
			platform->setPos(sf::Vector2f(door->GetPosition().x, door->GetFixtureList()->GetAABB(0).GetCenter().y));
	}
}

void DoorPlat::open()
{
	if (closed)
	{
		if (state == CLOSED)
		{
			eTime = 0.f;
			state = OPENING;
		}
		if (state == CLOSING)
		{
			eTime = mTime - eTime;
			state = OPENING;
		}
	}
	else
	{
		if (state == OPEN)
		{
			eTime = 0.f;
			state = CLOSING;
		}
		if (state == OPENING)
		{
			eTime = mTime - eTime;
			state == CLOSING;
		}
	}
}

void DoorPlat::close()
{
	if (closed)
	{
		if (state == OPEN)
		{
			eTime = 0.f;
			state = CLOSING;
		}
		if (state == OPENING)
		{
			eTime = mTime - eTime;
			state == CLOSING;
		}
	}
	else
	{
		if (state == CLOSED)
		{
			eTime = 0.f;
			state = OPENING;
		}
		if (state == CLOSING)
		{
			eTime = mTime - eTime;
			state = OPENING;
		}
	}
}

sf::Vector2f DoorPlat::getPlatPos()
{
	if (!rot)
		return sf::Vector2f(door->GetFixtureList()->GetAABB(0).GetCenter().x, door->GetPosition().y);
	else
		return sf::Vector2f(door->GetPosition().x, door->GetFixtureList()->GetAABB(0).GetCenter().y);
}
