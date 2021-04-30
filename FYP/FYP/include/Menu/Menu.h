#pragma once
/*!
\file Menu.h
*/

#include <SFML/Graphics.hpp>
#include <iostream>

#include "TextureManager.h"

/*! \class Menu
\brief The main menu screen
*/
class Menu : public Texture
{
private:
	bool play;					//!< If normal play has been selected
	bool network;				//!< If network play has been selected
	bool networkText;			//!< If the network text options should be shown
	bool host;					//!< If host has been selected
	bool close;					//!< If close has been selected
	int selectedItemIndex;		//!< Which item in the index was selcted
	float width, height;		//!< The width and height of the window

	sf::Text menue[3];	//!< Menu text
	sf::Font font;		//!< Font used

	sf::View view;		//!< What the screen is looking at

protected:
	TextureManager * texManager = TextureManager::getInstance();	//!< The texture manager

public:
	Menu() {};
	Menu(float width, float height);		//!< Constructor
	void update(float timestep); //!< Update the menu with give timestep
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw the menu to the render context
	void processKeyPress(sf::Keyboard::Key code);		//!< Decides what to do on key press
	bool getPlay() { return play; }		//!< Returns the play bool
	bool getNetwork() { return network; }		//!< Returns the network bool
	bool getHost() { return host; }		//!< Returns the host bool
	bool getClose() { return close; }	//!< Returns the close bool
	void setPlay(bool Play);		//!< Sets the play bool
	void setNetwork(bool Network) { network = Network; }		//!< Sets the network bool
	void moveUp();		//!< Move up in the index (text options)
	void moveDown();	//!< Move down in the index (text options)
	void selected();	//!< What to do when an option is selected
};