#pragma once

#include "GameState.h"

class MenuState : public State
{
private:

public:
	MenuState();
	virtual ~MenuState() override;		//!< Deconstructor
	virtual void update(float timestep) override;		//!< Updates all game elements
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;		//!< Draws all game elements
};