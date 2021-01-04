#include "Game.h"

Game::Game()
{
	view.setCenter(0.f, 0.f);
	view.setSize(worldSize);

	world = new b2World(gravity);

	debugDraw.setWorld(world);

	playerOne = new Player(world, sf::Vector2f(0.5f, .0f), sf::Vector2f(0.1f, 0.6f), 0.f);
	platform[0] = new Platform(world, sf::Vector2f(0.0f, 1.0f), sf::Vector2f(5.0f, 0.5f), 0.f);

	debug = false;
}

Game::~Game()
{
	// Clean up all pointers
	delete world;
	world = nullptr;

	delete playerOne;
	playerOne = nullptr;

	for (Platform* plat : platform)
	{
		delete plat;
		plat = nullptr;
	}
}

void Game::update(float timestep)
{
	// Update the world
	world->Step(timestep, velIterations, posIterations);

	// Update each dyanmic element - effectively update render information
	playerOne->update(timestep);

	// Delete debug shapes
	if (debug) debugDraw.clear();
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// Set the view
	target.setView(view);

	target.draw(*playerOne);
	for (Platform *plat : platform) target.draw(*plat);


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
		playerOne->moveRight();
		break;
	case sf::Keyboard::A:
		playerOne->moveLeft();
		break;
	case sf::Keyboard::W:
		playerOne->jump();
		break;
	}

}