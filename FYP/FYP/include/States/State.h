#pragma once
/*!
\file State.h
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>

/*! \class Level
\brief Base class for all states
*/
class State : public sf::Drawable
{
protected:
	std::stack<State *>* states;

public:
	virtual ~State() = default;
	virtual void update(float timestep) = 0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
	virtual void processKeyPress(sf::Keyboard::Key code) = 0;		//!< Decides what to do on key press
	virtual void processKeyRelease(sf::Keyboard::Key code) = 0;		//!< Decides what to do on key release
	virtual bool getQuit() = 0;
};