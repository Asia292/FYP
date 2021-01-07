#include "DoorPlat.h"

DoorPlat::DoorPlat(b2World * world, const sf::Vector2f& position, const float orientation)
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

	//// DOOR ////
	shape.SetAsBox(0.5f * 0.5f, 0.16f * 0.5f, b2Vec2(-0.25f, 0.f), 0.f);
	door->CreateFixture(&fixtureDef);
	//// ANCHOR/SIDE ////
	shape.SetAsBox(0.7f * 0.5f, 0.04f * 0.5f, b2Vec2(-0.85f, -0.10f), 0.f);
	top->CreateFixture(&fixtureDef);
	shape.SetAsBox(0.7f * 0.5f, 0.04f * 0.5f, b2Vec2(-0.85f, 0.10f), 0.f);
	top->CreateFixture(&fixtureDef);
	shape.SetAsBox(0.18f * 0.5f, 0.18f * 0.5f, b2Vec2(-1.11f, 0.f), 0.f);
	top->CreateFixture(&fixtureDef);

	//// JOINT ////
	door->SetType(b2BodyType::b2_dynamicBody);
	b2MotorJointDef jointDef;
	jointDef.Initialize(top, door);
	jointDef.maxForce = 1000.0f; // Force much large than we'd ever need
	jointDef.maxTorque = 1000.0f; // Avoid rotation with high torque
	motor = (b2MotorJoint*)world->CreateJoint(&jointDef);

	//// SFML ////
	Top.setPosition(sf::Vector2f(top->GetPosition().x - 0.85, top->GetPosition().y));
	Top.setSize(sf::Vector2f(0.7f, 0.2f));
	Top.setOrigin(Top.getSize() * 0.5f);
	Top.setFillColor(sf::Color(60, 60, 60));
	Top.setOutlineThickness(0.f);

	Door.setPosition(sf::Vector2f(door->GetFixtureList()->GetAABB(0).GetCenter().x, door->GetPosition().y));
	Door.setSize(sf::Vector2f(0.5f, 0.16f));
	Door.setOrigin(Door.getSize() * 0.5f);
	Door.setFillColor(sf::Color(90, 45, 0));
	Door.setOutlineThickness(0.f);
	

	mTime = 1.5f;
	state = CLOSED;
}

void DoorPlat::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(Door);
	target.draw(Top);
}

void DoorPlat::setUserData(void *data)
{
	door->SetUserData(data);
	top->SetUserData(data);
}

void DoorPlat::update(float timestep)
{

	if (state == OPENING)
	{
		eTime += timestep;

		float t = eTime / mTime;
		float dist;

		if (t < 1.0f)
			dist = t * -0.5f;
		else
		{
			dist = -0.5f;
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
			dist = (1.0f - t)*-0.5f;
		else
		{
			dist = 0.0f;
			state = CLOSED;
		}

		motor->SetLinearOffset(b2Vec2(dist, 0));
	}

	Door.setPosition(sf::Vector2f(door->GetFixtureList()->GetAABB(0).GetCenter().x, door->GetPosition().y));
}

void DoorPlat::open()
{
	//std::cout << "Opening" << std::endl;
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

void DoorPlat::close()
{
	//std::cout << "Closing" << std::endl;
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