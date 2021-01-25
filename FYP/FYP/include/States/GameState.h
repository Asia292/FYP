#pragma once
/*!
\file GameState.h
*/

#include "State.h"
#include "Game.h"

/*! \class GameState
\brief State which holds the game
*/
class GameState : public State
{
private:
	Game *game;		//!< Pointer to the game
	bool quit;		//!< If game scene should close

public:
	GameState(int level, int *levelScore, std::stack<State *>* States);		//!< Constructor
	virtual ~GameState() override;		//!< Override base deconstructor
	virtual void update(float timestep) override;		//!< Override base update
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;		//!< Override base draw
	virtual void processKeyPress(sf::Keyboard::Key code) override;		//!< Override base key press
	virtual void processKeyRelease(sf::Keyboard::Key code) override;		//!< Override base key release
	virtual bool getQuit() override { return quit; }		//!< Override base quit - returns quit bool
};