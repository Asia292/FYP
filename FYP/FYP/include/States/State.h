#pragma once
/*!
\file State.h
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include <list>

/*! \class Level
\brief Base class for all states
*/
class State : public sf::Drawable
{
protected:
	std::stack<State *>* states;		//!< Pointer to the stack of states

public:
	virtual ~State() = default;		//!< Deconstructor
	virtual void update(float timestep) = 0;	//!< Updates the scene/state
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;		//!< Draws everything to screen
	virtual void processKeyPress(sf::Keyboard::Key code) = 0;		//!< Decides what to do on key press
	virtual void processKeyRelease(sf::Keyboard::Key code) = 0;		//!< Decides what to do on key release
	virtual bool getQuit() = 0;		//!< If the state should quit
};