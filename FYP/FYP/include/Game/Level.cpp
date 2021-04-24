#include "Level.h"

Level::Level(TextureManager * textMan, b2World * world, int level, bool onClient)
{
	lEmpty = true;
	dEmpty = true;
	client = onClient;

	switch (level)
	{
	case 0:
		doc.load_file(".\\assets\\xml\\Level1.xml");
		break;
	case 1:
		doc.load_file(".\\assets\\xml\\Level2.xml");
		break;
	case 2:
		doc.load_file(".\\assets\\xml\\Level3.xml");
		break;
	case 3:
		doc.load_file(".\\assets\\xml\\Level4.xml");
		break;
	case 4:
		doc.load_file(".\\assets\\xml\\Level5.xml");
		break;
	}

	lvl = doc.child("Level"); 


	textMan->setTexture(lvl.attribute("background").as_string(), this);
	setBg();
	textMan->setTexture(lvl.attribute("cover").as_string(), &cover);
	cover.setBg();

	lvlTime = lvl.attribute("time").as_float();

	//// PLAYERS ////
	pos = lvl.child("lightPlayer").child("position");
	lightPlayer = new Player(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()), sf::Vector2f(0.4f, 0.6f), 0.f, 0x0010, textMan, onClient);
	pos = lvl.child("darkPlayer").child("position");
	darkPlayer = new Player(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()), sf::Vector2f(0.4f, 0.6f), 0.f, 0x0100, textMan, onClient);

	//// PICKUPS ////
	for (curr = lvl.child("darkPickUp"); curr; curr = curr.next_sibling("darkPickUp"))
	{
		pos = curr.child("position");

		darkPickUps.push_back(new PickUp(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(0.3f, 0.3f), 0x0100, textMan));
	}

	for (curr = lvl.child("lightPickUp"); curr; curr = curr.next_sibling("lightPickUp"))
	{
		pos = curr.child("position");

		lightPickUps.push_back(new PickUp(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(0.3f, 0.3f), 0x0010, textMan));
	}

	//// HAZARDS ////
	for ( curr = lvl.child("hazard"); curr; curr = curr.next_sibling("hazard"))
	{
		pos = curr.child("position");
		size = curr.child("size");

		hazards.push_back(new Hazard(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()),
			0.f, curr.attribute("mask").as_uint()));

		hazards.back()->setUserData(new std::pair<std::string, void *>(typeid(decltype(*hazards.back())).name(), hazards.back()));
	}

	//// MOVINGPLATS ////
	for (curr = lvl.child("movingPlat"); curr; curr = curr.next_sibling("movingPlat"))
	{
		pos = curr.child("position");
		size = curr.child("size");
		pugi::xml_node end = curr.child("end");

		movingPlats.push_back(new MovingPlat(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()),
			curr.attribute("orientation").as_float(),
			sf::Vector2f(end.attribute("x").as_float(), end.attribute("y").as_float()),
			textMan, curr.attribute("colour").as_string(), curr.attribute("glow").as_string(), onClient));

		movePlatPosBefore.push_back(movingPlats.back()->getBody()->GetPosition());

		movingPlats.back()->setUserData(new std::pair<std::string, void *>(typeid(decltype(*movingPlats.back())).name(), movingPlats.back()));
	}

	//// DOORPLATS ////
	for (curr = lvl.child("door"); curr; curr = curr.next_sibling("door"))
	{
		pos = curr.child("position");
		size = curr.child("size");

		doorPlats.push_back(new DoorPlat(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()),
			curr.attribute("orientation").as_float(), curr.attribute("close").as_bool(),
			textMan, curr.attribute("glow").as_string(), onClient));

		doorPosBefore.push_back(doorPlats.back()->getPlatPos());

		doorPlats.back()->setUserData(new std::pair<std::string, void *>(typeid(decltype(*doorPlats.back())).name(), doorPlats.back()));
	}

	//// TILTPLATS ////
	for (curr = lvl.child("tilt"); curr; curr = curr.next_sibling("tilt"))
	{
		pos = curr.child("position");
		size = curr.child("size");

		tiltPlats.push_back(new TiltingPlat(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()),
			sf::Vector2f(0.f, 0.f), curr.attribute("orientation").as_float(), textMan,
			curr.attribute("texture").as_string(), onClient));

		tiltAngleBefore.push_back(tiltPlats.back()->getBody()->GetAngle());

		tiltPlats.back()->setUserData(new std::pair<std::string, void *>(typeid(decltype(*tiltPlats.back())).name(), tiltPlats.back()));
	}

	//// LEVERS ////
	for (curr = lvl.child("lever"); curr; curr = curr.next_sibling("lever"))
	{
		pos = curr.child("position");
		size = curr.child("size");

		if (curr.attribute("name").as_string() == std::string("movingPlat"))
		{
			levers.push_back(new Lever(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
				sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()),
				movingPlats[curr.attribute("index").as_int()], curr.attribute("right").as_bool(), textMan,
				curr.attribute("colour").as_string(), curr.attribute("back").as_string()));
		}
		else if (curr.attribute("name").as_string() == std::string("door"))
		{
			levers.push_back(new Lever(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
				sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()),
				doorPlats[curr.attribute("index").as_int()], curr.attribute("right").as_bool(), textMan,
				curr.attribute("colour").as_string(), curr.attribute("back").as_string()));
		}

		leverFrameBefore.push_back(levers.back()->getFrame());

		levers.back()->setUserData(levers.back());
	}

	//// BUTTONS ////
	for (curr = lvl.child("button"); curr; curr = curr.next_sibling("button"))
	{
		pos = curr.child("position");

		if (curr.attribute("name").as_string() == std::string("movingPlat"))
		{
			buttons.push_back(new Button(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
				sf::Vector2f(0.6f, 0.3f), movingPlats[curr.attribute("index").as_int()],
				textMan, curr.attribute("colour").as_string()));
		}
		else if (curr.attribute("name").as_string() == std::string("door"))
		{
			buttons.push_back(new Button(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
				sf::Vector2f(0.6f, 0.3f), doorPlats[curr.attribute("index").as_int()],
				textMan, curr.attribute("colour").as_string()));
		}

		buttons.back()->setUserData(buttons.back());
	}

	//// BLOCKS ////
	for (curr = lvl.child("block"); curr; curr = curr.next_sibling("block"))
	{
		pos = curr.child("position");

		if (curr.attribute("type").as_string() == std::string("block"))
		{
			blocks.push_back(new Block(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
				sf::Vector2f(0.5f, 0.5f), 0.f, textMan, onClient));
		}
		else if (curr.attribute("type").as_string() == std::string("ball"))
		{
			blocks.push_back(new Block(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
				0.12f, 0.f, textMan, onClient));
		}

		blockPosBefore.push_back(blocks.back()->getBody()->GetPosition());

		blocks.back()->setUserData(new std::pair<std::string, void *>(typeid(decltype(*blocks.back())).name(), blocks.back()));
	}

	//// DRAFTS ////
	for (curr = lvl.child("draft"); curr; curr = curr.next_sibling("draft"))
	{
		pos = curr.child("position");
		size = curr.child("size");

		drafts.push_back(new Draft(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()),
			curr.attribute("angle").as_float()));

		drafts.back()->setUserData(drafts.back());
	}

	//// HOME ////
	curr = lvl.child("lightHome");
	pos = curr.child("position");
	size = curr.child("size");
	lightHome = new HomeSensor(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
		sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()), lightPlayer, textMan);

	lightHomeBefore = false;

	curr = lvl.child("darkHome");
	pos = curr.child("position");
	size = curr.child("size");
	darkHome = new HomeSensor(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
		sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()), darkPlayer, textMan);

	darkHomeBefore = false;

	//// FLOOR/OUTLINE ////
	for (curr = lvl.child("outline"); curr; curr = curr.next_sibling("outline"))
	{
		outline.clear();
		for (pugi::xml_node coord = curr.child("coord"); coord; coord = coord.next_sibling("coord"))
		{
			outline.push_back(b2Vec2(coord.attribute("x").as_float(), coord.attribute("y").as_float()));
		}
		floors.push_back(new Floor(outline.data(), outline.size(), world));
	}


	//// USER DATA ////
	lightPlayer->setUserData(new std::pair<std::string, void *>(typeid(decltype(*lightPlayer)).name(), lightPlayer));
	darkPlayer->setUserData(new std::pair<std::string, void *>(typeid(decltype(*darkPlayer)).name(), darkPlayer));

	for (PickUp *item : lightPickUps) item->setUserData(item);
	for (PickUp *item : darkPickUps) item->setUserData(item);

	lightHome->setUserData(lightHome);
	darkHome->setUserData(darkHome);

	for (Floor *floor : floors) floor->setUserData(new std::pair<std::string, void *>(typeid(decltype(*floor)).name(), floor));
}

Level::~Level()
{
	delete lightPlayer;
	lightPlayer = nullptr;
	delete darkPlayer;
	darkPlayer = nullptr;

	delete lightHome;
	lightHome = nullptr;
	delete darkHome;
	darkHome = nullptr;

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

	for (Floor *floor : floors)
	{
		delete floor;
		floor = nullptr;
	}

	
	for (Hazard *hazard : hazards)
	{
		delete hazard;
		hazard = nullptr;
	}

	
	for (MovingPlat *plat : movingPlats)
	{
		delete plat;
		plat = nullptr;
	}

	for (DoorPlat *plat : doorPlats)
	{
		delete plat;
		plat = nullptr;
	}

	
	for (TiltingPlat *plat : tiltPlats)
	{
		delete plat;
		plat = nullptr;
	}

	
	for (Lever *lever : levers)
	{
		delete lever;
		lever = nullptr;
	}

	
	for (Button *button : buttons)
	{
		delete button;
		button = nullptr;
	}

	
	for (Block *block : blocks)
	{
		delete block;
		block = nullptr;
	}

	
	for (Draft *draft : drafts)
	{
		delete draft;
		draft = nullptr;
	}
}

void Level::update(float timestep, bool server)
{
	Texture::update(timestep);
	cover.update(timestep);

	lightPlayer->update(timestep);
	darkPlayer->update(timestep);

	lightHome->update(timestep);
	darkHome->update(timestep);

	for (MovingPlat *plat : movingPlats)
	{
		plat->update(timestep);
	}
	
	for (DoorPlat *plat : doorPlats)
	{
		plat->update(timestep);
	}

	for (TiltingPlat *plat : tiltPlats)
	{
		plat->update(timestep);
	}

	for (Lever *lever : levers)
	{
		lever->update(timestep);
	}
	
	for (Button *button : buttons)
	{
		button->update(timestep);
	}

	for (Block *block : blocks)
	{
		block->update(timestep);
	}

	for (Draft *draft : drafts)
	{
		draft->update(timestep);
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

void Level::draw(sf::RenderTarget &target, sf::RenderStates states)
{
	target.draw(currSprite, states);
	
	for (MovingPlat *plat : movingPlats)
	{
		target.draw(*plat);
	}
	
	for (DoorPlat *plat : doorPlats)
	{
		target.draw(*plat);
	}

	for (TiltingPlat *plat : tiltPlats)
	{
		target.draw(*plat);
	}

	for (Button *button : buttons)
	{
		target.draw(*button);
	}

	for (Block *block : blocks)
	{
		target.draw(*block);
	}

	for (PickUp *item : lightPickUps)
	{
		if (item != nullptr)
			target.draw(*item);
	}
	for (PickUp *item : darkPickUps)
	{
		if (item != nullptr)
			target.draw(*item);
	}

	target.draw(*lightHome);
	target.draw(*darkHome);

	target.draw(*lightPlayer);
	target.draw(*darkPlayer);

	target.draw(cover, states);

	for (Lever *lever : levers)
	{
		target.draw(*lever);
	}
}

int Level::score(float time)
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

	if (lEmpty && dEmpty && (time < lvlTime))
		return 3;
	else if (!lEmpty && !dEmpty && (time > lvlTime))
		return 1;
	else
		return 2;
}

void Level::networkFrameUpdate(Server * server)
{
	for (int i = 0; i < movingPlats.size(); i++)
	{
		if (movingPlats[i]->getBody()->GetPosition() != movePlatPosBefore[i])
		{
			sf::Packet p;
			StampPacket(PacketType::LevelUpdate, p);
			LevelUpdate update;
			float x = movingPlats[i]->getBody()->GetPosition().x;
			float y = movingPlats[i]->getBody()->GetPosition().y;
			update.object = 0;
			update.index = i;
			update.position = sf::Vector2f(x, y);
			update.texture = movingPlats[i]->getGlow();
			p << update;
			server->Broadcast(p);

			movePlatPosBefore[i] = movingPlats[i]->getBody()->GetPosition();
		}
	}

	for (int i = 0; i < doorPlats.size(); i++)
	{
		if (doorPlats[i]->getPlatPos() != doorPosBefore[i])
		{
			sf::Packet p;
			StampPacket(PacketType::LevelUpdate, p);
			LevelUpdate update;
			float x = doorPlats[i]->getPlatPos().x;
			float y = doorPlats[i]->getPlatPos().y;
			update.object = 1;
			update.index = i;
			update.position = sf::Vector2f(x, y);
			p << update;
			server->Broadcast(p);

			doorPosBefore[i] = doorPlats[i]->getPlatPos();
		}
	}

	for (int i = 0; i < tiltPlats.size(); i++)
	{
		if (tiltPlats[i]->getBody()->GetAngle() != tiltAngleBefore[i])
		{
			sf::Packet p;
			StampPacket(PacketType::LevelUpdate, p);
			LevelUpdate update;
			update.object = 2;
			update.index = i;
			update.angle = tiltPlats[i]->getBody()->GetAngle();
			p << update;
			server->Broadcast(p);

			tiltAngleBefore[i] = tiltPlats[i]->getBody()->GetAngle();
		}
	
	}

	for (int i = 0; i < levers.size(); i++)
	{
		if (levers[i]->getFrame() != leverFrameBefore[i])
		{
			sf::Packet p;
			StampPacket(PacketType::LevelUpdate, p);
			LevelUpdate update;
			update.object = 3;
			update.index = i;
			update.texture = levers[i]->getTexture();
			update.frame = levers[i]->getFrame();
			p << update;
			server->Broadcast(p);

			leverFrameBefore[i] = levers[i]->getFrame();
		}
	}

	for (int i = 0; i < blocks.size(); i++)
	{
		if (blocks[i]->getBody()->GetPosition() != blockPosBefore[i])
		{
			sf::Packet p;
			StampPacket(PacketType::LevelUpdate, p);
			LevelUpdate update;
			float x = blocks[i]->getBody()->GetPosition().x;
			float y = blocks[i]->getBody()->GetPosition().y;
			update.object = 4;
			update.index = i;
			update.position = sf::Vector2f(x, y);
			update.angle = blocks[i]->getBody()->GetAngle();
			p << update;
			server->Broadcast(p);

			blockPosBefore[i] = blocks[i]->getBody()->GetPosition();
		}
	}

	for (int i = 0; i < lightPickUps.size(); i++)
	{
		if (lightPickUps[i] != nullptr && lightPickUps[i]->getDel())
		{
			delete lightPickUps[i];
			lightPickUps[i] = nullptr;

			sf::Packet p;
			StampPacket(PacketType::LevelUpdate, p);
			LevelUpdate update;
			update.object = 5;
			update.index = i;
			p << update;
			server->Broadcast(p);
		}
	}

	for (int i = 0; i < darkPickUps.size(); i++)
	{
		if (darkPickUps[i] != nullptr && darkPickUps[i]->getDel())
		{
			delete darkPickUps[i];
			darkPickUps[i] = nullptr;

			sf::Packet p;
			StampPacket(PacketType::LevelUpdate, p);
			LevelUpdate update;
			update.object = 6;
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
		update.object = 7;
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
		update.object = 8;
		update.texture = darkHome->getFade();
		p << update;
		server->Broadcast(p);

		std::cout << darkHomeBefore << std::endl;
	}
}

void Level::networkUpdate(int object, int index, bool texture, int frame, float angle, sf::Vector2f position)
{
	float deg;
	switch (object)
	{
	case 0:
		movingPlats[index]->setPos(position);
		movingPlats[index]->setTexture(texture);
		break;
	case 1:
		doorPlats[index]->setPlatPos(position);
		break;
	case 2:
		deg = angle * 57.29577f;
		tiltPlats[index]->setAngle(deg);
		break;
	case 3:
		levers[index]->setTexture(texture);
		levers[index]->setFrame(frame);
		break;
	case 4:
		blocks[index]->setPos(position);
		deg = angle * 57.29577f;
		blocks[index]->setAngle(deg);
		break;
	case 5:
		lightPickUps[index]->delTrue();
		break;
	case 6:
		darkPickUps[index]->delTrue();
		break;
	case 7:
		lightHome->setFade(texture);
		break;
	case 8:
		darkHome->setFade(texture);
		break;
	}
}