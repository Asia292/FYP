#include "Lvl2.h"

Lvl2::Lvl2(TextureManager * textMan, b2World * world, bool onClient)
{
	textMan->setTexture("lvl2", this);
	setBg();

	lEmpty = true;
	dEmpty = true;
	client = onClient;

	doc.load_file(".\\assets\\xml\\Level2.xml");
	pugi::xml_node lvl = doc.child("Level2");

	//// PLAYERS ////
	lightPlayer = new Player(world, sf::Vector2f(0.70f, 9.40f), sf::Vector2f(0.4f, 0.6f), 0.f, 0x0010, textMan, onClient);
	darkPlayer = new Player(world, sf::Vector2f(1.50f, 9.40f), sf::Vector2f(0.4f, 0.6f), 0.f, 0x0100, textMan, onClient);

	//// HAZARDS ////
	int i = 0;
	for (pugi::xml_node curr = lvl.child("hazard"); curr; curr = curr.next_sibling("hazard"))
	{
		pugi::xml_node pos = curr.child("position");
		pugi::xml_node size = curr.child("size");

		hazards[i++] = new Hazard(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()),
			0.f, curr.attribute("mask").as_uint());
	}

	//// TILTING PLATS ////
	i = 0;
	for (pugi::xml_node curr = lvl.child("tilt"); curr; curr = curr.next_sibling("tilt"))
	{
		pugi::xml_node pos = curr.child("position");
		pugi::xml_node size = curr.child("size");

		tilt[i++] = new TiltingPlat(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()),
			sf::Vector2f(0.f, 0.f), 0.f, textMan, "lvl2Tilt", onClient);
	}

	//// DOOR/SLIDING PLATS ////
	i = 0;
	for (pugi::xml_node curr = lvl.child("door"); curr; curr = curr.next_sibling("door"))
	{
		pugi::xml_node pos = curr.child("position");
		pugi::xml_node size = curr.child("size");
		pugi::xml_node cover = curr.child("coverPos");

		slide[i++] = new DoorPlat(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()),
			sf::Vector2f(cover.attribute("x").as_float(), cover.attribute("y").as_float()),
			curr.attribute("orientation").as_float(), curr.attribute("close").as_bool(), textMan,
			curr.attribute("glow").as_string(), curr.attribute("cover").as_string(), onClient);
	}

	//// BUTTONS ////
	i = 0;
	for (pugi::xml_node curr = lvl.child("button"); curr; curr = curr.next_sibling("button"))
	{
		pugi::xml_node pos = curr.child("position");

		buttons[i++] = new Button(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(0.6f, 0.3f), slide[curr.attribute("door").as_int()], textMan, curr.attribute("colour").as_string());
	}

	//// PICKUPS ////
	i = 0;
	for (pugi::xml_node curr = lvl.child("darkPickUp"); curr; curr = curr.next_sibling("darkPickUp"))
	{
		pugi::xml_node pos = curr.child("position");

		darkPickUps[i++] = new PickUp(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(0.3f, 0.3f), 0x0100, textMan);
	}

	i = 0;
	for (pugi::xml_node curr = lvl.child("lightPickUp"); curr; curr = curr.next_sibling("lightPickUp"))
	{
		pugi::xml_node pos = curr.child("position");

		lightPickUps[i++] = new PickUp(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(0.3f, 0.3f), 0x0010, textMan);
	}

	//// HOME ////
	pugi::xml_node curr = lvl.child("lightHome");
	pugi::xml_node pos = curr.child("position");
	pugi::xml_node size = curr.child("size");
	lightHome = new HomeSensor(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
		sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()), lightPlayer, textMan);

	curr = lvl.child("darkHome");
	pos = curr.child("position");
	size = curr.child("size");
	darkHome = new HomeSensor(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
		sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()), darkPlayer, textMan);

	//// FLOOR/OUTLINE ////
	i = 0;
	curr = lvl.child("outline");
	for (pugi::xml_node coord = curr.child("coord"); coord; coord = coord.next_sibling("coord"))
	{
		outlineOne[i++].Set(coord.attribute("x").as_float(), coord.attribute("y").as_float());
	}
	floors[0] = new Floor(outlineOne, 38, world);

	i = 0;
	curr = curr.next_sibling("outline");
	for (pugi::xml_node coord = curr.child("coord"); coord; coord = coord.next_sibling("coord"))
	{
		outlineTwo[i++].Set(coord.attribute("x").as_float(), coord.attribute("y").as_float());
	}
	floors[1] = new Floor(outlineTwo, 11, world);

	i = 0;
	curr = curr.next_sibling("outline");
	for (pugi::xml_node coord = curr.child("coord"); coord; coord = coord.next_sibling("coord"))
	{
		outlineThree[i++].Set(coord.attribute("x").as_float(), coord.attribute("y").as_float());
	}
	floors[2] = new Floor(outlineThree, 7, world);

	i = 0;
	curr = curr.next_sibling("outline");
	for (pugi::xml_node coord = curr.child("coord"); coord; coord = coord.next_sibling("coord"))
	{
		outlineFour[i++].Set(coord.attribute("x").as_float(), coord.attribute("y").as_float());
	}
	floors[3] = new Floor(outlineFour, 7, world);


	//// USER DATA ////
	for(Floor *floor : floors) floor->setUserData(new std::pair<std::string, void *>(typeid(decltype(*floor)).name(), floor));

	lightPlayer->setUserData(new std::pair<std::string, void *>(typeid(decltype(*lightPlayer)).name(), lightPlayer));
	darkPlayer->setUserData(new std::pair<std::string, void *>(typeid(decltype(*darkPlayer)).name(), darkPlayer));
	
	for (Hazard *haz : hazards) haz->setUserData(new std::pair<std::string, void *>(typeid(decltype(*haz)).name(), haz));
	for (Button *button : buttons) button->setUserData(button);
	for (TiltingPlat *platform : tilt) platform->setUserData(new std::pair<std::string, void *>(typeid(decltype(*platform)).name(), platform));
	for (DoorPlat *platform : slide) platform->setUserData(new std::pair<std::string, void *>(typeid(decltype(*platform)).name(), platform));

	for (PickUp *item : lightPickUps) item->setUserData(item);
	for (PickUp *item : darkPickUps) item->setUserData(item);

	lightHome->setUserData(lightHome);
	darkHome->setUserData(darkHome);

	//// NETWORK BEFORE VALUES ////
	for (int i = 0; i < 2; i++) doorPosBefore[i] = slide[i]->getPlatPos();
	for (int i = 0; i < 2; i++) tiltAngleBefore[i] = tilt[i]->getBody()->GetAngle();
	lightHomeBefore = false;
	darkHomeBefore = false;
}

Lvl2::~Lvl2()
{
	for (Hazard *haz : hazards)
	{
		delete haz;
		haz = nullptr;
	}

	for (TiltingPlat *plat : tilt)
	{
		delete plat;
		plat = nullptr;
	}

	for (DoorPlat *door : slide)
	{
		delete door;
		door = nullptr;
	}

	for (Button *button : buttons)
	{
		delete button;
		button = nullptr;
	}

	for (PickUp *item : lightPickUps)
	{
		if (item != nullptr)
		{
			delete item;
			item = nullptr;
		}
	}
	for (PickUp *item : darkPickUps)
	{
		if (item != nullptr)
		{
			delete item;
			item = nullptr;
		}
	}

	delete lightHome;
	lightHome = nullptr;
	delete darkHome;
	darkHome = nullptr;

	delete lightPlayer;
	lightPlayer = nullptr;
	delete darkPlayer;
	darkPlayer = nullptr;
}

void Lvl2::update(float timestep, bool server)
{
	Texture::update(timestep);

	lightPlayer->update(timestep);
	darkPlayer->update(timestep);

	lightHome->update(timestep);
	darkHome->update(timestep);

	for (TiltingPlat *plat : tilt)
	{
		plat->update(timestep);
	}

	for (DoorPlat *door : slide)
	{
		door->update(timestep);
	}

	for (Button *button : buttons)
	{
		button->update(timestep);
	}

	int i = 0;
	for (PickUp *item : lightPickUps)
	{
		if (item != nullptr)
		{
			item->update(timestep);

			if (item->getDel() && !server)
			{
				delete item;
				lightPickUps[i] = nullptr;
			}
		}
		i++;
	}
	i = 0;
	for (PickUp *item : darkPickUps)
	{
		if (item != nullptr)
		{
			item->update(timestep);

			if (item->getDel() && !server)
			{
				delete item;
				darkPickUps[i] = nullptr;
			}
		}
		i++;
	}
}

void Lvl2::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(currSprite, states);

	target.draw(*lightHome);
	target.draw(*darkHome);

	for (TiltingPlat *plat : tilt)
	{
		target.draw(*plat);
	}

	for (DoorPlat *door : slide)
	{
		door->draw(target, states);
	}

	for (Button *button : buttons)
	{
		target.draw(*button);
	}

	for (PickUp *item : lightPickUps)
	{
		if (item != nullptr)
			item->draw(target, states);
	}
	for (PickUp *item : darkPickUps)
	{
		if (item != nullptr)
			item->draw(target, states);
	}

	target.draw(*lightPlayer);
	target.draw(*darkPlayer);
}

int Lvl2::score(float time)
{
	for (PickUp *item : lightPickUps)
	{
		if (item != nullptr)
			lEmpty = false;
	}
	for (PickUp *item : darkPickUps)
	{
		if (item != nullptr)
			dEmpty = false;
	}

	if (lEmpty && dEmpty && (time < 60.f))
		return 3;
	else if (!lEmpty && !dEmpty && (time > 60.f))
		return 1;
	else
		return 2;
}

void Lvl2::networkFrameUpdate(Server * server)
{
	for (int i = 0; i < 2; i++)
	{
		if (tilt[i]->getBody()->GetAngle() != tiltAngleBefore[i])
		{
			sf::Packet p;
			StampPacket(PacketType::LevelUpdate, p);
			LevelUpdate update;
			update.object = 0;
			update.index = i;
			update.angle = tilt[i]->getBody()->GetAngle();
			p << update;
			server->Broadcast(p);

			tiltAngleBefore[i] = tilt[i]->getBody()->GetAngle();
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (slide[i]->getPlatPos() != doorPosBefore[i])
		{
			sf::Packet p;
			StampPacket(PacketType::LevelUpdate, p);
			LevelUpdate update;
			float x = slide[i]->getPlatPos().x;
			float y = slide[i]->getPlatPos().y;
			update.object = 1;
			update.index = i;
			update.position = sf::Vector2f(x, y);
			p << update;
			server->Broadcast(p);

			doorPosBefore[i] = slide[i]->getPlatPos();
		}
	}

	for (int i = 0; i < 8; i++)
	{
		if (lightPickUps[i] != nullptr && lightPickUps[i]->getDel())
		{
			delete lightPickUps[i];
			lightPickUps[i] = nullptr;

			sf::Packet p;
			StampPacket(PacketType::LevelUpdate, p);
			LevelUpdate update;
			update.object = 2;
			update.index = i;
			p << update;
			server->Broadcast(p);
		}

		if (darkPickUps[i] != nullptr && darkPickUps[i]->getDel())
		{
			delete darkPickUps[i];
			darkPickUps[i] = nullptr;

			sf::Packet p;
			StampPacket(PacketType::LevelUpdate, p);
			LevelUpdate update;
			update.object = 3;
			update.index = i;
			p << update;
			server->Broadcast(p);
		}
	}

	if (lightHome->getFade() != lightHomeBefore)
	{
		sf::Packet p;
		StampPacket(PacketType::LevelUpdate, p);
		LevelUpdate update;
		update.object = 4;
		update.texture = lightHome->getFade();
		p << update;
		server->Broadcast(p);

		lightHomeBefore = lightHome->getFade();
	}

	if (darkHome->getFade() != darkHomeBefore)
	{
		sf::Packet p;
		StampPacket(PacketType::LevelUpdate, p);
		LevelUpdate update;
		update.object = 5;
		update.texture = darkHome->getFade();
		p << update;
		server->Broadcast(p);

		std::cout << darkHomeBefore << std::endl;
	}
}

void Lvl2::networkUpdate(int object, int index, bool texture, int frame, float angle, sf::Vector2f position)
{
	float deg;
	switch (object)
	{
	case 0:
		deg = angle * 57.29577f;
		tilt[index]->setAngle(deg);
		break;
	case 1:
		slide[index]->setPlatPos(position);
		break;
	case 2:
		lightPickUps[index]->delTrue();
		break;
	case 3:
		darkPickUps[index]->delTrue();
		break;
	case 4:
		lightHome->setFade(texture);
		break;
	case 5:
		darkHome->setFade(texture);
		break;
	}
}
