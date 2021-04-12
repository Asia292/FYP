#include "Lvl1.h"

Lvl1::Lvl1(TextureManager * textMan, b2World * world, bool onClient)
{
	textMan->setTexture("lvl1", this);
	setBg();

	lEmpty = true;
	dEmpty = true;
	client = onClient;

	doc.load_file(".\\assets\\xml\\Level1.xml");
	pugi::xml_node lvl = doc.child("Level1");

	/*hazards.resize(3);
	lightPickUps.resize(3);
	darkPickUps.resize(3);
	levers.resize(1);
	buttons.resize(2);
	movingPlats.resize(2);
	blocks.resize(1);
	floors.resize(1);*/

	//// PLAYERS ////
	lightPlayer = new Player(world, sf::Vector2f(1.00f, 8.14f), sf::Vector2f(0.4f, 0.6f), 0.f, 0x0010, textMan, onClient);
	darkPlayer = new Player(world, sf::Vector2f(1.00f, 9.62f), sf::Vector2f(0.4f, 0.6f), 0.f, 0x0100, textMan, onClient);

	//// HAZARDS ////
	/*lightHazard = new Hazard(world, sf::Vector2f(10.25f, 10.18f), sf::Vector2f(1.5f, 0.25f), 0.f, 0x0010);
	darkHazard = new Hazard(world, sf::Vector2f(7.39f, 10.18f), sf::Vector2f(1.5f, 0.25f), 0.f, 0x0100);
	bothHazard = new Hazard(world, sf::Vector2f(9.54f, 8.00f), sf::Vector2f(1.5f, 0.25f), 0.f, 0xFFFF);*/
	
	for (pugi::xml_node curr = lvl.child("hazard"); curr; curr = curr.next_sibling("hazard"))
	{
		pugi::xml_node pos = curr.child("position");
		pugi::xml_node size = curr.child("size");

		hazards.push_back(new Hazard(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()),
			0.f, curr.attribute("mask").as_uint()));
	}

	//// PLATFORMS ////
	//platforms[0] = new MovingPlat(world, sf::Vector2f(1.09f, 5.55f), sf::Vector2f(1.47f, 0.26f), 0.f, sf::Vector2f(1.09f, 6.60f), textMan, "yellowPlat", "yellowGlow", onClient);
	//platforms[1] = new MovingPlat(world, sf::Vector2f(12.96f, 4.24f), sf::Vector2f(1.47f, 0.26f), 0.f, sf::Vector2f(12.96f, 5.60f), textMan, "purplePlat", "purpleGlow", onClient);

	for (pugi::xml_node curr = lvl.child("movingPlat"); curr; curr = curr.next_sibling("platform"))
	{
		pugi::xml_node pos = curr.child("position");
		pugi::xml_node size = curr.child("size");
		pugi::xml_node end = curr.child("end");

		movingPlats.push_back(new MovingPlat(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()),
			curr.attribute("orientation").as_float(), 
			sf::Vector2f(end.attribute("x").as_float(), end.attribute("y").as_float()),
			textMan, curr.attribute("colour").as_string(), curr.attribute("glow").as_string(), onClient));

		movePlatPosBefore.push_back(movingPlats.back()->getBody()->GetPosition());
	}

	//// LEVERS/BUTTONS ////
	/*lever = new Lever(world, sf::Vector2f(3.77f, 7.0f), sf::Vector2f(0.6f, 0.5f), platforms[0], true, textMan, "yellowLever", "yellowLeverReverse");
	buttons[0] = new Button(world, sf::Vector2f(5.42f, 5.31f), sf::Vector2f(0.6f, 0.3f), platforms[1], textMan, "purpleButton");
	buttons[1] = new Button(world, sf::Vector2f(11.16f, 3.85f), sf::Vector2f(0.6f, 0.3f), platforms[1], textMan, "purpleButton");
	*/
	pugi::xml_node curr = lvl.child("lever");
	pugi::xml_node pos = curr.child("position");
	pugi::xml_node size = curr.child("size");
	levers.push_back(new Lever(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
		sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()),
		movingPlats[curr.attribute("platform").as_int()], curr.attribute("right").as_bool(), textMan,
		curr.attribute("colour").as_string(), curr.attribute("back").as_string()));

	leverFrameBefore.push_back(levers.back()->getFrame());

	for (pugi::xml_node curr = lvl.child("button"); curr; curr = curr.next_sibling("button"))
	{
		pugi::xml_node pos = curr.child("position");
		pugi::xml_node size = curr.child("size");

		buttons.push_back(new Button(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()),
			movingPlats[curr.attribute("platform").as_int()], textMan, curr.attribute("colour").as_string()));
	}

	//// ITEMS ////
	/*darkPickUps[0] = new PickUp(world, sf::Vector2f(7.39f, 9.00f), sf::Vector2f(0.3f, 0.3f), 0x0100, textMan);
	darkPickUps[1] = new PickUp(world, sf::Vector2f(5.23f, 6.81f), sf::Vector2f(0.3f, 0.3f), 0x0100, textMan);
	darkPickUps[2] = new PickUp(world, sf::Vector2f(4.36f, 1.04f), sf::Vector2f(0.3f, 0.3f), 0x0100, textMan);

	lightPickUps[0] = new PickUp(world, sf::Vector2f(10.25f, 9.00f), sf::Vector2f(0.3f, 0.3f), 0x0010, textMan);
	lightPickUps[1] = new PickUp(world, sf::Vector2f(3.60f, 5.04f), sf::Vector2f(0.3f, 0.3f), 0x0010, textMan);
	lightPickUps[2] = new PickUp(world, sf::Vector2f(1.10f, 2.11f), sf::Vector2f(0.3f, 0.3f), 0x0010, textMan);*/

	for (pugi::xml_node curr = lvl.child("darkPickUp"); curr; curr = curr.next_sibling("darkPickUp"))
	{
		pugi::xml_node pos = curr.child("position");

		darkPickUps.push_back(new PickUp(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(0.3f, 0.3f), 0x0100, textMan));
	}

	for (pugi::xml_node curr = lvl.child("lightPickUp"); curr; curr = curr.next_sibling("lightPickUp"))
	{
		pugi::xml_node pos = curr.child("position");

		lightPickUps.push_back(new PickUp(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
			sf::Vector2f(0.3f, 0.3f), 0x0010, textMan));
	}

	//// MISC ////
	/*block = new Block(world, sf::Vector2f(7.56f, 3.04f), sf::Vector2f(0.5f, 0.5f), 0.f, textMan, onClient);

	lightHome = new HomeSensor(world, sf::Vector2f(11.89f, 1.71f), sf::Vector2f(0.68f, 0.92f), lightPlayer, textMan);
	darkHome = new HomeSensor(world, sf::Vector2f(13.18f, 1.71f), sf::Vector2f(0.68f, 0.92f), darkPlayer, textMan);
	*/
	curr = lvl.child("block");
	pos = curr.child("position");
	size = curr.child("size");
	blocks.push_back(new Block(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
		sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()), 0.f, textMan, onClient));

	blockPosBefore.push_back(blocks.back()->getBody()->GetPosition());

	curr = lvl.child("lightHome");
	pos = curr.child("position");
	size = curr.child("size");
	lightHome = new HomeSensor(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
		sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()), lightPlayer, textMan);

	curr = lvl.child("darkHome");
	pos = curr.child("position");
	size = curr.child("size");
	darkHome = new HomeSensor(world, sf::Vector2f(pos.attribute("x").as_float(), pos.attribute("y").as_float()),
		sf::Vector2f(size.attribute("x").as_float(), size.attribute("y").as_float()), darkPlayer, textMan);

	//// FLOOR/OUTLINE ////
	for (pugi::xml_node curr = lvl.child("outline").child("coord"); curr; curr = curr.next_sibling("coord"))
	{
		outline.push_back(b2Vec2(curr.attribute("x").as_float(), curr.attribute("y").as_float()));
	}

	/*outline[0].Set(0.33f, 0.31f);
	outline[1].Set(13.71f, 0.31f);
	outline[2].Set(13.71f, 2.18f);
	outline[3].Set(5.81f, 2.16f);
	outline[4].Set(5.43f, 1.79f);
	outline[5].Set(5.05f, 1.80f);
	outline[6].Set(4.69f, 1.43f);
	outline[7].Set(3.95f, 1.44f);
	outline[8].Set(3.64f, 1.78f);
	outline[9].Set(3.95f, 1.78f);

	outline[10].Set(4.33f, 2.15f);
	outline[11].Set(4.33f, 3.22f);
	outline[12].Set(6.11f, 3.22f);
	outline[13].Set(6.11f, 2.50f);
	outline[14].Set(13.71f, 2.50f);
	outline[15].Set(13.71f, 5.76f);
	outline[16].Set(7.58f, 5.76f);
	outline[17].Set(7.22f, 5.40f);
	outline[18].Set(1.81f, 5.40f);
	outline[19].Set(1.81f, 5.73f);

	outline[20].Set(6.45f, 5.73f);
	outline[21].Set(6.84f, 6.10f);
	outline[22].Set(11.51f, 6.10f);
	outline[23].Set(11.89f, 6.47f);
	outline[24].Set(12.24f, 6.47f);
	outline[25].Set(12.98f, 7.19f);
	outline[26].Set(13.71f, 7.19f);
	outline[27].Set(13.71f, 9.01f);
	outline[28].Set(12.98f, 9.01f);
	outline[29].Set(12.63f, 9.35f);

	outline[30].Set(12.63f, 10.10f);
	outline[31].Set(11.17f, 10.10f);
	outline[32].Set(10.80f, 10.31f);
	outline[33].Set(9.75f, 10.30f);
	outline[34].Set(9.39f, 10.09f);
	outline[35].Set(8.31f, 10.09f);
	outline[36].Set(7.93f, 10.29f);
	outline[37].Set(6.84f, 10.29f);
	outline[38].Set(6.50f, 10.10f);
	outline[39].Set(0.33f, 10.10f);

	outline[40].Set(0.33f, 8.99f);
	outline[41].Set(4.66f, 8.99f);
	outline[42].Set(4.66f, 8.65f);
	outline[43].Set(0.33f, 8.65f);
	outline[44].Set(0.33f, 7.54f);
	outline[45].Set(5.39f, 7.54f);
	outline[46].Set(6.12f, 8.27f);
	outline[47].Set(12.23f, 8.27f);
	outline[48].Set(11.91f, 7.93f);
	outline[49].Set(6.86f, 7.93f);

	outline[50].Set(6.14f, 7.21f);
	outline[51].Set(0.33f, 7.21f);
	outline[52].Set(0.33f, 4.30f);
	outline[53].Set(10.07f, 4.30f);
	outline[54].Set(10.46f, 4.66f);
	outline[55].Set(12.24f, 4.66f);
	outline[56].Set(12.24f, 3.96f);
	outline[57].Set(10.46f, 3.96f);
	outline[58].Set(9.75f, 3.24f);
	outline[59].Set(7.22f, 3.24f);

	outline[60].Set(7.22f, 3.96f);
	outline[61].Set(2.14f, 3.96f);
	outline[62].Set(2.14f, 2.51f);
	outline[63].Set(0.33f, 2.51f);
	outline[64].Set(0.33f, 0.31f);*/

	floors.push_back(new Floor(outline.data(), outline.size(), world));


	//// USER DATA ////
	for (Floor *floor : floors) floor->setUserData(new std::pair<std::string, void *>(typeid(decltype(*floor)).name(), floor));

	lightPlayer->setUserData(new std::pair<std::string, void *>(typeid(decltype(*lightPlayer)).name(), lightPlayer));
	darkPlayer->setUserData(new std::pair<std::string, void *>(typeid(decltype(*darkPlayer)).name(), darkPlayer));

	/*lightHazard->setUserData(new std::pair<std::string, void *>(typeid(decltype(*lightHazard)).name(), lightHazard));
	darkHazard->setUserData(new std::pair<std::string, void *>(typeid(decltype(*darkHazard)).name(), darkHazard));
	bothHazard->setUserData(new std::pair<std::string, void *>(typeid(decltype(*bothHazard)).name(), bothHazard));
	*/
	for (Hazard *haz : hazards) haz->setUserData(new std::pair<std::string, void *>(typeid(decltype(*haz)).name(), haz));


	for (Lever *lever : levers) lever->setUserData(lever);
	for (Button *button : buttons) button->setUserData(button);
	for (MovingPlat *platform : movingPlats) platform->setUserData(new std::pair<std::string, void *>(typeid(decltype(*platform)).name(), platform));

	for (PickUp *item : lightPickUps) item->setUserData(item);
	for (PickUp *item : darkPickUps) item->setUserData(item);

	for (Block *block : blocks) block->setUserData(new std::pair<std::string, void *>(typeid(decltype(*block)).name(), block));
	lightHome->setUserData(lightHome);
	darkHome->setUserData(darkHome);

	//// NETWORK BEFORE VALUES	////
	/*frameBefore = lever->getFrame();
	for (int i = 0; i < 2; i++) platPosBefore[i] = platforms[i]->getBody()->GetPosition();
	blockPosBefore = block->getBody()->GetPosition();*/
	lightHomeBefore = false;
	darkHomeBefore = false;
}

Lvl1::~Lvl1()
{
	delete lightPlayer;
	lightPlayer = nullptr;
	delete darkPlayer;
	darkPlayer = nullptr;

	/*delete lightHazard;
	lightHazard = nullptr;
	delete darkHazard;
	darkHazard = nullptr;*/

	for (Hazard *haz : hazards)
	{
		delete haz;
		haz = nullptr;
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
	for (MovingPlat *platform : movingPlats)
	{
		delete platform;
		platform = nullptr;
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

	for (Block *block : blocks)
	{
		delete block;
		block = nullptr;
	}

	for (Floor *floor : floors)
	{
		delete floor;
		floor = nullptr;
	}

	delete lightHome;
	lightHome = nullptr;
	delete darkHome;
	darkHome = nullptr;
}

void Lvl1::update(float timestep, bool server)
{
	Texture::update(timestep);

	lightPlayer->update(timestep);
	darkPlayer->update(timestep);

	for (MovingPlat *platform : movingPlats)
	{
		platform->update(timestep);
	}
	for (Button *button : buttons)
	{
		button->update(timestep);
	}
	for (Lever *lever : levers)
	{
		lever->update(timestep);
	}
	for (Block *block : blocks)
	{
		block->update(timestep);
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

	lightHome->update(timestep);
	darkHome->update(timestep);
}

void Lvl1::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(currSprite, states);

	/*target.draw(*lightHazard);
	target.draw(*darkHazard);
	target.draw(*bothHazard);*/

	for (Hazard *haz : hazards)
	{
		target.draw(*haz);
	}

	for (Lever *lever : levers)
	{
		target.draw(*lever);
	}
	for (Button *button : buttons)
	{
		target.draw(*button);
	}
	for (MovingPlat *platform : movingPlats)
	{
		target.draw(*platform);
	}
	for (Block *block : blocks)
	{
		target.draw(*block);
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

	target.draw(*lightHome);
	target.draw(*darkHome);

	target.draw(*lightPlayer);
	target.draw(*darkPlayer);
}

int Lvl1::score(float time)
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

void Lvl1::networkFrameUpdate(Server * server)
{
	for (int i = 0; i < levers.size(); i++)
	{
		if (levers[i]->getFrame() != leverFrameBefore[i])
		{
			sf::Packet p;
			StampPacket(PacketType::LevelUpdate, p);
			LevelUpdate update;
			update.object = 0;
			update.index = i;
			update.texture = levers[i]->getTexture();
			update.frame = levers[i]->getFrame();
			p << update;
			server->Broadcast(p);

			leverFrameBefore[i] = levers[i]->getFrame();
		}
	}

	for (int i = 0; i < movingPlats.size(); i++)
	{
		if (movingPlats[i]->getBody()->GetPosition() != movePlatPosBefore[i])
		{
			sf::Packet p;
			StampPacket(PacketType::LevelUpdate, p);
			LevelUpdate update;
			float x = movingPlats[i]->getBody()->GetPosition().x;
			float y = movingPlats[i]->getBody()->GetPosition().y;
			update.object = 1;
			update.index = i;
			update.position = sf::Vector2f(x, y);
			update.texture = movingPlats[i]->getGlow();
			p << update;
			server->Broadcast(p);

			movePlatPosBefore[i] = movingPlats[i]->getBody()->GetPosition();
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
			update.object = 2;
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
			update.object = 3;
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
			update.object = 4;
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
		update.object = 5;
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
		update.object = 6;
		update.texture = darkHome->getFade();
		p << update;
		server->Broadcast(p);

		std::cout << darkHomeBefore << std::endl;
	}
}

void Lvl1::networkUpdate(int object, int index, bool texture, int frame, float angle, sf::Vector2f position)
{
	float deg;
	switch (object)
	{
	case 0:
		levers[index]->setTexture(texture);
		levers[index]->setFrame(frame);
		break;
	case 1:
		movingPlats[index]->setPos(position);
		movingPlats[index]->setTexture(texture);
		break;
	case 2:
		blocks[index]->setPos(position);
		deg = angle * 57.29577f;
		blocks[index]->setAngle(deg);
		break;
	case 3:
		lightPickUps[index]->delTrue();
		break;
	case 4:
		darkPickUps[index]->delTrue();
		break;
	case 5:
		lightHome->setFade(texture);
		break;
	case 6:
		darkHome->setFade(texture);
		break;
	}
}
