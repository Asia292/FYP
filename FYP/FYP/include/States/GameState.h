#pragma once

#include "State.h"
#include "Game.h"

class GameState : public State
{
private:
	Game *game;
	bool quit;

public:
	GameState(int level, std::stack<State *>* States);
	virtual ~GameState() override;		//!< Deconstructor
	virtual void update(float timestep) override;		//!< Updates all game elements
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;		//!< Draws all game elements
	virtual void processKeyPress(sf::Keyboard::Key code) override;		//!< Decides what to do on key press
	virtual void processKeyRelease(sf::Keyboard::Key code) override;		//!< Decides what to do on key release
	virtual bool getQuit() override { return quit; }
};