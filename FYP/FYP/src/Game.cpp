#include "Game.h"

Game::Game()
{
	/*
	TO DO
			X Lever
			X Tilting platform
			X Pickup
			X Movable object
			X Finish contact listener
				X Player is grounded
				X Player dies
			X Floor
			X Texture manager
			- HUD
			X Home sensor
			- Game over
			- Level complete
			- Level class
	*/
	view.setCenter(7.f, 5.2f);
	view.setSize(worldSize);

	world = new b2World(gravity);
	world->SetContactListener(&listener);

	debugDraw.setWorld(world);

	currLevel = new Lvl1(texManager, world);

	debug = false;
	lightRight = false;
	lightLeft = false;
	darkRight = false;
	darkLeft = false;


	//// USER DATA ////
	/*lightPlayer->setUserData(new std::pair<std::string, void *>(typeid(decltype(*lightPlayer)).name(), lightPlayer));
	darkPlayer->setUserData(new std::pair<std::string, void *>(typeid(decltype(*darkPlayer)).name(), darkPlayer));

	door->setUserData(new std::pair<std::string, void *>(typeid(decltype(*door)).name(), door));
	move->setUserData(new std::pair<std::string, void *>(typeid(decltype(*move)).name(), move));
	button->setUserData(button);
	tilt->setUserData(new std::pair<std::string, void *>(typeid(decltype(*tilt)).name(), tilt));

	for (PlatTemp *plat : platform) plat->setUserData(new std::pair<std::string, void *>(typeid(decltype(*plat)).name(), plat));

	for (Hazard *hazard : darkHazards) hazard->setUserData(new std::pair<std::string, void *>(typeid(decltype(*hazard)).name(), hazard));
	for (Hazard *hazard : lightHazards) hazard->setUserData(new std::pair<std::string, void *>(typeid(decltype(*hazard)).name(), hazard));
	for (Hazard *hazard : bothHazards) hazard->setUserData(new std::pair<std::string, void *>(typeid(decltype(*hazard)).name(), hazard));

	for (PickUp *item : lightPickUps) item->setUserData(item);

	for (Block *block : blocks) block->setUserData(new std::pair<std::string, void *>(typeid(decltype(*block)).name(), block));*/
}

Game::~Game()
{
	// Clean up all pointers
	delete world;
	world = nullptr;

	delete currLevel;
	currLevel = nullptr;

	TextureManager::delInstance();
}

void Game::update(float timestep)
{
	// Update the world
	world->Step(timestep, velIterations, posIterations);

	if (lightLeft)
		currLevel->lightPlayer->moveLeft();
	else if (lightRight)
		currLevel->lightPlayer->moveRight();
	else
		currLevel->lightPlayer->idle();

	if (darkRight)
		currLevel->darkPlayer->moveRight();
	else if (darkLeft)
		currLevel->darkPlayer->moveLeft();
	else
		currLevel->darkPlayer->idle();

	currLevel->update(timestep);
	// Delete debug shapes
	if (debug) debugDraw.clear();
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// Set the view
	target.setView(view);

	currLevel->draw(target, sf::RenderStates::Default);
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
		currLevel->lightPlayer->jump();
		break;
	case sf::Keyboard::Right:
		darkRight = true;
		break;
	case sf::Keyboard::Left:
		darkLeft = true;
		break;
	case sf::Keyboard::Up:
		currLevel->darkPlayer->jump();
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
