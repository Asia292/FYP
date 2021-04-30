#pragma once
/*!
\file GameState.h
*/

#include "State.h"
#include "Game.h"

/*! \class GameState
\brief Derives from base state class - holds and manages the game
*/
class GameState : public State
{
private:
	Game *game;		//!< Pointer to the game
	bool quit;		//!< If game scene should close
	Server* server;	//!< On the server or not
	int lvl;		//!< The level to load
	int *lvlScore;	//!< A pointer to the level score recieved from the level select
	bool gameOver;	//!< If the game is over or not
	bool onServer;	//!< If the state is loaded server side
	bool onClient;	//!< If the state is loaded client side

public:
	GameState(int level, int *levelScore, std::stack<State *>* States, Server* l_server = nullptr);		//!< Constructor
	virtual ~GameState() override;		//!< Override base deconstructor
	virtual void update(float timestep) override;		//!< Override base update
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;		//!< Override base draw
	virtual void processKeyPress(sf::Keyboard::Key code) override;		//!< Overrides base key press
	virtual void processNetworkKeyPress(int code, Server* l_server, int id) override;		//!< Overrides base network key press
	virtual void processKeyRelease(sf::Keyboard::Key code) override;		//!< Overrides base key release
	virtual void processNetworkKeyRelease(int code, Server* l_server, int id) override;		//!< Overrides base network key release
	virtual bool getQuit() override { return quit; }		//!< Override base quit - returns quit bool

	//Function per packet type
	virtual void levelSelectUpdate(int lvl, int back) override;		//!< Updates the game time values, takes same values as level select update so same function is overriden - used only for networking
	virtual void stateTransition(bool push) override;		//!< Signifies if a state should be pushed or popped - used only for networking
	virtual void playerUpdate(int player, int texture, int frame, bool flip, bool dead, sf::Vector2f pos) override;		//!< Updates the player - used only for networking
	virtual void levelUpdate(int object, int index, bool texture, int frame, float angle, sf::Vector2f position) override;		//!< Updates all other objects in a level except the player - used only for networking
	virtual void timeUpdate(int minute, int second) override;		//!< Updates the time for the level - used only for networking
};