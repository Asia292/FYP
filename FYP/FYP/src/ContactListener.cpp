#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact * contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	std::pair<std::string, void *> *dataA = (std::pair<std::string, void *>*) bodyA->GetUserData();
	std::pair<std::string, void *> *dataB = (std::pair<std::string, void *>*) bodyB->GetUserData();

	bool sensorA = contact->GetFixtureA()->IsSensor();
	bool sensorB = contact->GetFixtureB()->IsSensor();



	if (sensorA)
	{
		Sensor * sensor = static_cast<Sensor *>(bodyA->GetUserData());
		sensor->onAction(bodyB);
	}
	if (sensorB)
	{
		Sensor * sensor = static_cast<Sensor *>(bodyB->GetUserData());
		sensor->onAction(bodyA);
	}

	if (typeid(Player).name() == dataA->first)
	{
		if (typeid(Hazard).name() == dataB->first)
		{
			std::cout << "Hit" << std::endl;
		}
	}

	if (typeid(Hazard).name() == dataA->first)
	{
		if (typeid(Player).name() == dataB->first)
		{
			std::cout << "Hit" << std::endl;
		}
	}
}

void ContactListener::EndContact(b2Contact * contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	std::pair<std::string, void *> *dataA = (std::pair<std::string, void *>*) bodyA->GetUserData();
	std::pair<std::string, void *> *dataB = (std::pair<std::string, void *>*) bodyB->GetUserData();

	bool sensorA = contact->GetFixtureA()->IsSensor();
	bool sensorB = contact->GetFixtureB()->IsSensor();



	if (sensorA)
	{
		Sensor * sensor = static_cast<Sensor *>(bodyA->GetUserData());
		sensor->offAction(bodyB);
	}
	if (sensorB)
	{
		Sensor * sensor = static_cast<Sensor *>(bodyB->GetUserData());
		sensor->offAction(bodyA);
	}
}
