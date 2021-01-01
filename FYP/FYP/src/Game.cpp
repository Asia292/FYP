#include "Game.h"

Game::Game()
{
	view.setCenter(0.f, 0.f);
	view.setSize(worldSize);

	world = new b2World(gravity);

	debugDraw.setWorld(world);
}

Game::~Game()
{
	// Clean up all pointers
	delete world;
	world = nullptr;
}

void Game::update(float timestep)
{
	// Delete debug shapes
	if (debug) debugDraw.clear();

}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
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
	}
	
}