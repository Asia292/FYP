#pragma once
/*!
\file LevelSelectState.h
*/

#include "GameState.h"
#include "LevelSelect.h"

/*! \class LevelSelectState
\brief The state which holds the level select screen
*/
class LevelSelectState : public State
{
private:
	bool quit;		//!< If the state should quit
	LevelSelect * levelSelect;		//!< Pointer to the level select 

public:
	LevelSelectState(float Height, float Width, std::stack<State *>* States);		//!< Constructior
	virtual ~LevelSelectState() override;		//!< Overrides base deconstructor
	virtual void update(float timestep) override;		//!< Overrides base update
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;		//!< Overrides base draw
	virtual void processKeyPress(sf::Keyboard::Key code) override;		//!< Overrides base key press
	virtual void processKeyRelease(sf::Keyboard::Key code) override;		//!< Overrides base key release
	virtual bool getQuit() override { return quit; }	//!< Overrides base quit - returns quit bool
};