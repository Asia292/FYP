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
			Player * player = static_cast<Player*>(dataA->second);
			player->setDead(true);
		}
		if (typeid(DoorPlat).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataA->second);
			player->setGrounded(true);
		}
		if (typeid(TiltingPlat).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataA->second);
			player->setGrounded(true);
		}
		if (typeid(MovingPlat).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataA->second);
			player->setGrounded(true);

			b2Vec2 velo = bodyB->GetLinearVelocity();
			bodyA->SetLinearVelocity(velo);
		}
		if (typeid(Floor).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataA->second);
			player->setGrounded(true);
		}

		if (typeid(Block).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataA->second);
			player->setGrounded(true);
		}
	}

	if (typeid(Hazard).name() == dataA->first)
	{
		if (typeid(Player).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataA->second);
			player->setDead(true);
		}
	}

	if (typeid(DoorPlat).name() == dataA->first)
	{
		if (typeid(Player).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataB->second);
			player->setGrounded(true);
		}
	}

	if (typeid(MovingPlat).name() == dataA->first)
	{
		if (typeid(Player).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataB->second);
			player->setGrounded(true);

			b2Vec2 velo = bodyA->GetLinearVelocity();
			bodyB->SetLinearVelocity(velo);
		}
	}

	if (typeid(TiltingPlat).name() == dataA->first)
	{
		if (typeid(Player).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataB->second);
			player->setGrounded(true);
		}
	}

	if (typeid(Floor).name() == dataA->first)
	{
		if (typeid(Player).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataB->second);
			player->setGrounded(true);
		}
	}

	if (typeid(Block).name() == dataA->first)
	{
		if (typeid(Player).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataB->second);
			player->setGrounded(true);
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

	if (typeid(Player).name() == dataA->first)
	{
		if (typeid(DoorPlat).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataA->second);
			player->setGrounded(false);
		}
		if (typeid(TiltingPlat).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataA->second);
			player->setGrounded(false);
		}
		if (typeid(MovingPlat).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataA->second);
			player->setGrounded(false);
		}
		if (typeid(Floor).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataA->second);
			player->setGrounded(false);
		}
		if (typeid(Block).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataA->second);
			player->setGrounded(false);
		}
	}

	if (typeid(DoorPlat).name() == dataA->first)
	{
		if (typeid(Player).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataB->second);
			player->setGrounded(false);
		}
	}

	if (typeid(MovingPlat).name() == dataA->first)
	{
		if (typeid(Player).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataB->second);
			player->setGrounded(false);
		}
	}

	if (typeid(TiltingPlat).name() == dataA->first)
	{
		if (typeid(Player).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataB->second);
			player->setGrounded(false);
		}
	}

	if (typeid(Floor).name() == dataA->first)
	{
		if (typeid(Player).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataB->second);
			player->setGrounded(false);
		}
	}

	if (typeid(Block).name() == dataA->first)
	{
		if (typeid(Player).name() == dataB->first)
		{
			Player * player = static_cast<Player*>(dataB->second);
			player->setGrounded(false);
		}
	}
}
