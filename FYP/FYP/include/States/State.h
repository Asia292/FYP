#pragma once
/*!
\file State.h
*/

#include <SFML/Graphics.hpp>
#include "Server.h"
#include <iostream>
#include <stack>

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
	virtual void processNetworkKeyPress(int code, Server* l_server) = 0;		//!< Decides what to do on key press
	virtual void processKeyRelease(sf::Keyboard::Key code) = 0;		//!< Decides what to do on key release
	virtual void processNetworkKeyRelease(int code, Server* l_server) = 0;		//!< Decides what to do on key release
	virtual bool getQuit() = 0;		//!< If the state should quit

	//Function per packet type???
	virtual void levelUpdate(int lvl, int back) = 0;
	virtual void stateTransition(bool push) = 0;
	virtual void playerUpdate(int player, int texture, int frame, sf::Vector2f pos) = 0;
};