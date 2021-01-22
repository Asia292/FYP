#pragma once

#include "GameState.h"
#include "Menu.h"

class MenuState : public State
{
private:
	bool quit;
	Menu *menu;

public:
	MenuState(float Height, float Width, std::stack<State *>* States);
	virtual ~MenuState() override;		//!< Deconstructor
	virtual void update(float timestep) override;		//!< Updates all game elements
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;		//!< Draws all game elements
	virtual void processKeyPress(sf::Keyboard::Key code) override;		//!< Decides what to do on key press
	virtual void processKeyRelease(sf::Keyboard::Key code) override;		//!< Decides what to do on key release
	virtual bool getQuit() override { return quit; }
};