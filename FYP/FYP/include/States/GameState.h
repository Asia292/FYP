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
	Server* server;	//!< On the server or not
	int lvl;
	int *lvlScore;

public:
	GameState(int level, int *levelScore, std::stack<State *>* States, Server* l_server = nullptr);		//!< Constructor
	virtual ~GameState() override;		//!< Override base deconstructor
	virtual void update(float timestep) override;		//!< Override base update
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;		//!< Override base draw
	virtual void processKeyPress(sf::Keyboard::Key code) override;		//!< Overrides base key press
	virtual void processNetworkKeyPress(int code, Server* l_server) override;		//!< Overrides base network key press
	virtual void processKeyRelease(sf::Keyboard::Key code) override;		//!< Overrides base key release
	virtual void processNetworkKeyRelease(int code, Server* l_server) override;		//!< Overrides base network key release
	virtual bool getQuit() override { return quit; }		//!< Override base quit - returns quit bool

	//Function per packet type???
	virtual void levelUpdate(int lvl, int back) override {};
	virtual void stateTransition(bool push) override {};
	virtual void playerUpdate(int player, int texture, int frame, sf::Vector2f pos) override;
};