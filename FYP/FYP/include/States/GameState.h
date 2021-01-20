#pragma once

#include "State.h"
#include "Game.h"

class GameState : public State
{
private:
	Game *game;
public:
	GameState(int level);
	virtual ~GameState() override;		//!< Deconstructor
	virtual void update(float timestep) override;		//!< Updates all game elements
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;		//!< Draws all game elements
};