#include "GameState.h"

GameState::GameState(int level)
{
	game = new Game(level);
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
}

void GameState::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	game->draw(target, states);
}
