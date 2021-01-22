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
			X Game over return confirmation
			- Level score
	*/
	view.setCenter(7.f, 5.2f);
	view.setSize(worldSize);

	world = new b2World(gravity);
	world->SetContactListener(&listener);

	debugDraw.setWorld(world);

	font.loadFromFile(".\\assets\\neuropol.ttf");

	switch (level)
	{
	case 0:
		currLevel = new Lvl1(texManager, world);
		break;
	}
	
	hud = new HUD(texManager, font);

	debug = false;
	lightRight = false;
	lightLeft = false;
	darkRight = false;
	darkLeft = false;
	back = 0;
	levelSelect = false;

	finish.setFont(font);
	finish.setFillColor(sf::Color(35, 179, 241));
	finish.setOutlineColor(sf::Color::Black);
	finish.setOutlineThickness(3);
	finish.setCharacterSize(45);
	finish.setScale(sf::Vector2f(0.01f, 0.01f));

	select[0].setFont(font);
	select[0].setFillColor(sf::Color(100, 32, 188));
	select[0].setOutlineColor(sf::Color::Black);
	select[0].setOutlineThickness(3);
	select[0].setCharacterSize(45);
	select[0].setScale(sf::Vector2f(0.01f, 0.01f));
	select[0].setString("RETRY");
	select[0].setPosition(4.3f, 5.7f);

	select[1].setFont(font);
	select[1].setFillColor(sf::Color(255, 222, 0));
	select[1].setOutlineColor(sf::Color::Black);
	select[1].setOutlineThickness(3);
	select[1].setCharacterSize(45);
	select[1].setScale(sf::Vector2f(0.01f, 0.01f));
	select[1].setString("LEVELS");
	select[1].setPosition(7.3f, 5.7f);

	texManager->setTexture("over", &backing);
	backing.setBg();
	backing.setPos(sf::Vector2f(190.f, 250.f));

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
	
	backing.update(timestep);
	backing.setPos(sf::Vector2f(3.30f, 3.0f));

	if (currLevel->darkPlayer->getHome() && currLevel->lightPlayer->getHome())
	{
		over = true;
		finish.setString("LEVEL COMPLETE");
		finish.setPosition(4.2f, 3.7f);
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
		finish.setPosition(5.f, 3.7f);
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

	if (over)
	{
		backing.draw(target, states);
		target.draw(finish);
		target.draw(select[0]);
		target.draw(select[1]);
	}

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
		if (over)
			moveRight();
		else
			darkRight = true;
		break;
	case sf::Keyboard::Left:
		if (over)
			moveLeft();
		else
			darkLeft = true;
		break;
	case sf::Keyboard::Up:
		currLevel->darkPlayer->jump();
		break;
	case sf::Keyboard::Return:
		if (over)
			selected();
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

void Game::moveLeft()
{
	if (back - 1 >= 0)
	{
		select[back].setFillColor(sf::Color(255, 222, 0));
		back--;
		select[back].setFillColor(sf::Color(100, 32, 188));
	}
}

void Game::moveRight()
{
	if (back + 1 < 2)
	{
		select[back].setFillColor(sf::Color(255, 222, 0));
		back++;
		select[back].setFillColor(sf::Color(100, 32, 188));
	}
}

void Game::selected()
{
	switch (back)
	{
	case 0:
		std::cout << "RETRY NOT YET IMPLEMENTED" << std::endl;
		break;
	case 1:
		levelSelect = true;
		break;
	}
}
