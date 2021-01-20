#include "Game.h"

Game::Game(int level)
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
			X HUD
			X Home sensor
			X Game over
			X Level complete
			X Level class
	*/
	view.setCenter(7.f, 5.2f);
	view.setSize(worldSize);

	world = new b2World(gravity);
	world->SetContactListener(&listener);

	debugDraw.setWorld(world);

	font.loadFromFile(".\\assets\\neuropol.ttf");

	currLevel = new Lvl1(texManager, world);
	hud = new HUD(texManager, font);

	debug = false;
	lightRight = false;
	lightLeft = false;
	darkRight = false;
	darkLeft = false;

	finish.setFont(font);
	finish.setFillColor(sf::Color(35, 179, 241));
	finish.setOutlineColor(sf::Color::Black);
	finish.setOutlineThickness(3);
	finish.setCharacterSize(150);
	finish.setScale(sf::Vector2f(0.005f, 0.005f));

	over = false;
}

Game::~Game()
{
	// Clean up all pointers
	delete hud;
	hud = nullptr;

	delete currLevel;
	currLevel = nullptr;

	delete world;
	world = nullptr;

	TextureManager::delInstance();
}

void Game::update(float timestep)
{
	// Update the world
	world->Step(timestep, velIterations, posIterations);
	
	if (currLevel->darkPlayer->getHome() && currLevel->lightPlayer->getHome())
	{
		over = true;
		finish.setString("	 LEVEL \n COMPLETE");
		finish.setPosition(3.7f, 4.2f);
	}
	else if (!currLevel->darkPlayer->getDead() && !currLevel->lightPlayer->getDead())
	{
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
		hud->update(timestep);
	}
	else
	{
		over = true;
		finish.setString("GAME OVER");
		finish.setPosition(4.f, 4.7f);
	}
	// Delete debug shapes
	if (debug) debugDraw.clear();
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// Set the view
	target.setView(view);

	currLevel->draw(target, sf::RenderStates::Default);
	hud->draw(target, sf::RenderStates::Default);

	if(over)
		target.draw(finish);

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
