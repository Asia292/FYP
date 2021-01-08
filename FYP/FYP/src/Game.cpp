#include "Game.h"

Game::Game()
{
	/*
	TO DO
			X Lever
			- Tilting platform
			- Pickup
			- Movable object
			- Finish contact listener
			- Floor
			- Texture manager
			- HUD
			- Home sensor
	*/
	view.setCenter(0.f, 0.f);
	view.setSize(worldSize);

	world = new b2World(gravity);
	world->SetContactListener(&listener);

	debugDraw.setWorld(world);

	lightPlayer = new Player(world, sf::Vector2f(0.5f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0100, sf::Color::White);
	darkPlayer = new Player(world, sf::Vector2f(1.f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0010, sf::Color::Black);
	platform[0] = new PlatTemp(world, sf::Vector2f(0.0f, 1.0f), sf::Vector2f(5.0f, 0.5f), 0.f);
	darkHazards[0] = new Hazard(world, sf::Vector2f(-1.f, -1.f), sf::Vector2f(0.25f, 0.25f), 0.f, 0x0100, sf::Color::Black);
	lightHazards[0] = new Hazard(world, sf::Vector2f(1.5f, -1.f), sf::Vector2f(0.25f, 0.25f), 0.f, 0x0010, sf::Color::White);
	bothHazards[0] = new Hazard(world, sf::Vector2f(0.f, -1.f), sf::Vector2f(0.25f, 0.25f), 0.f, 0xFFFF, sf::Color::Blue);

	door = new DoorPlat(world, sf::Vector2f(-1.5f, 0.f), 0.f);
	move = new MovingPlat(world, sf::Vector2f(1.5f, 0.f), sf::Vector2f(0.5f, 0.1f), 0.f, sf::Vector2f(1.5f, -1.f));
	button = new Lever(world, sf::Vector2f(1.5f, 0.75f), sf::Vector2f(0.25f, 0.25f), move, false);

	tilt = new TiltingPlat(world, sf::Vector2f(-0.5, 0.6f), sf::Vector2f(1.f, 0.01f), sf::Vector2f(0.f, 0.f), 0.f, sf::Color::Cyan);

	debug = false;
	lightRight = false;
	lightLeft = false;
	darkRight = false;
	darkLeft = false;


	//// USER DATA ////
	lightPlayer->setUserData(new std::pair<std::string, void *>(typeid(decltype(*lightPlayer)).name(), lightPlayer));
	darkPlayer->setUserData(new std::pair<std::string, void *>(typeid(decltype(*darkPlayer)).name(), darkPlayer));

	door->setUserData(new std::pair<std::string, void *>(typeid(decltype(*door)).name(), door));
	move->setUserData(new std::pair<std::string, void *>(typeid(decltype(*move)).name(), move));
	button->setUserData(button);
	tilt->setUserData(new std::pair<std::string, void *>(typeid(decltype(*tilt)).name(), tilt));

	for (PlatTemp *plat : platform) plat->setUserData(new std::pair<std::string, void *>(typeid(decltype(*plat)).name(), plat));

	for (Hazard *hazard : darkHazards) hazard->setUserData(new std::pair<std::string, void *>(typeid(decltype(*hazard)).name(), hazard));
	for (Hazard *hazard : lightHazards) hazard->setUserData(new std::pair<std::string, void *>(typeid(decltype(*hazard)).name(), hazard));
	for (Hazard *hazard : bothHazards) hazard->setUserData(new std::pair<std::string, void *>(typeid(decltype(*hazard)).name(), hazard));
}

Game::~Game()
{
	// Clean up all pointers
	delete world;
	world = nullptr;

	delete lightPlayer;
	lightPlayer = nullptr;
	delete darkPlayer;
	darkPlayer = nullptr;

	delete door;
	door = nullptr;
	delete button;
	button = nullptr;
	delete move;
	move = nullptr;
	delete tilt;
	tilt = nullptr;

	for (PlatTemp* plat : platform)
	{
		delete button;
		button = nullptr;
	}
	for (Hazard* hazard : darkHazards)
	{
		delete hazard;
		hazard = nullptr;
	}
	for (Hazard* hazard : lightHazards)
	{
		delete hazard;
		hazard = nullptr;
	}
	for (Hazard* hazard : bothHazards)
	{
		delete hazard;
		hazard = nullptr;
	}
}

void Game::update(float timestep)
{
	// Update the world
	world->Step(timestep, velIterations, posIterations);

	// Update each dyanmic element - effectively update render information
	lightPlayer->update(timestep);
	darkPlayer->update(timestep);
	door->update(timestep);
	move->update(timestep);
	tilt->update(timestep);

	if (lightLeft)
		lightPlayer->moveLeft();
	if (lightRight)
		lightPlayer->moveRight();
	if (darkRight)
		darkPlayer->moveRight();
	if (darkLeft)
		darkPlayer->moveLeft();

	// Delete debug shapes
	if (debug) debugDraw.clear();
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// Set the view
	target.setView(view);

	target.draw(*lightPlayer);
	target.draw(*darkPlayer);
	for (PlatTemp *plat : platform) target.draw(*plat);
	for (Hazard *hazard : darkHazards) target.draw(*hazard);
	for (Hazard *hazard : lightHazards) target.draw(*hazard);
	for (Hazard *hazard : bothHazards) target.draw(*hazard);

	target.draw(*door);
	target.draw(*button);
	target.draw(*move);
	target.draw(*tilt);

	// Debug Draw
	if (debug) target.draw(debugDraw);
}

void Game::processKeyPress(sf::Keyboard::Key code)
{
	switch (code)
	{
	case sf::Keyboard::Tab:
		toggleDebug();
		break;
	case sf::Keyboard::D:
		lightRight = true;
		break;
	case sf::Keyboard::A:
		lightLeft = true;
		break;
	case sf::Keyboard::W:
		lightPlayer->jump();
		break;
	case sf::Keyboard::Right:
		darkRight = true;
		break;
	case sf::Keyboard::Left:
		darkLeft = true;
		break;
	case sf::Keyboard::Up:
		darkPlayer->jump();
		break;
	}

}

void Game::processKeyRelease(sf::Keyboard::Key code)
{
	switch (code)
	{
	case sf::Keyboard::D:
		lightRight = false;
		break;
	case sf::Keyboard::A:
		lightLeft = false;
		break;
	case sf::Keyboard::Right:
		darkRight = false;
		break;
	case sf::Keyboard::Left:
		darkLeft = false;
		break;
	}
}
