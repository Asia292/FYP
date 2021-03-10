#pragma once
/*!
\file MenuState.h
*/

#include "NetworkState.h"
#include "..\Menu\Menu.h"

/*! \class MenuState
\brief The state which holds the main menu
*/
class MenuState : public State
{
private:
	bool quit;		//!< If the state should quit
	Menu *menu;		//!< Pointer to the main menu

	int height, width;		//!< Height and width of the window

public:
	MenuState(float Height, float Width, std::stack<State *>* States);		//!< Constructior
	virtual ~MenuState() override;		//!< Overrides base deconstructor
	virtual void update(float timestep) override;		//!< Overrides base update
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;		//!< Overrides base draw
	virtual void processKeyPress(sf::Keyboard::Key code) override;		//!< Overrides base key press
	virtual void processNetworkKeyPress(int code, Server* l_server) override {};		//!< Overrides base network key press
	virtual void processKeyRelease(sf::Keyboard::Key code) override {};		//!< Overrides base key release
	virtual void processNetworkKeyRelease(int code, Server* l_server) override {};		//!< Overrides base network key release
	virtual bool getQuit() override { return quit; }	//!< Overrides base quit - returns quit bool

	//Function per packet type???
	virtual void levelUpdate(int lvl, int back) override {};
	virtual void stateTransition(bool push) override {};
	virtual void playerUpdate(int player, int texture, int frame, sf::Vector2f pos) override {};
};