#include "GameState.h"

GameState::GameState(int level, std::stack<State *>* States)
{
	states = States;
	game = new Game(level);
	quit = false;
}

GameState::~GameState()
{
	game->~Game();

	delete game;
	game = nullptr;
}

void GameState::update(float timestep)
{
	game->update(timestep);

	if (game->getOver())
		quit = true;
}

void GameState::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	game->draw(target, states);
}

void GameState::processKeyPress(sf::Keyboard::Key code)
{
	game->processKeyPress(code);
}

void GameState::processKeyRelease(sf::Keyboard::Key code)
{
	game->processKeyRelease(code);
}
