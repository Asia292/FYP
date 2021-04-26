#pragma once
/*!
\file State.h
*/

#include <SFML/Graphics.hpp>
#include "Server.h"
#include <iostream>
#include <stack>

/*! \class Level
\brief Base class for all states, all functions are virtual to be overrided.
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
	virtual void processNetworkKeyPress(int code, Server* l_server, int id) = 0;		//!< Decides what to do on key press
	virtual void processKeyRelease(sf::Keyboard::Key code) = 0;		//!< Decides what to do on key release
	virtual void processNetworkKeyRelease(int code, Server* l_server, int id) = 0;		//!< Decides what to do on key release
	virtual bool getQuit() = 0;		//!< If the state should quit

	//Function per packet type
	virtual void levelSelectUpdate(int lvl, int back) = 0;		//!< Updates the level select values - used only for networking
	virtual void stateTransition(bool push) = 0;		//!< Signifies if a state should be pushed or popped - used only for networking
	virtual void playerUpdate(int player, int texture, int frame, bool flip, bool dead, sf::Vector2f pos) = 0;		//!< Updates the player - used only for networking
	virtual void levelUpdate(int object, int index, bool texture, int frame, float angle, sf::Vector2f position) = 0;		//!< Updates all other objects in a level except the player - used only for networking
	virtual void timeUpdate(int minute, int second) = 0;		//!< Updates the time for the level - used only for networking
};