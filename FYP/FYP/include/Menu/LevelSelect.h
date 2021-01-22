#pragma once
/*!
\file LevelSelect.h
*/

#include <SFML/Graphics.hpp>
#include <iostream>

#include "TextureManager.h"

/*! \class LevelSelect
\brief The level select screen
*/
class LevelSelect : public Texture
{
private:
	bool close;
	bool play;
	int selectedLevel;
	int back;
	float y;

	sf::RectangleShape menuBox;
	sf::RectangleShape backing[5];
	Texture preview;
	sf::Text menu;
	sf::Text levels[5];	//!< Level text
	sf::Font font;		//!< Font used

	sf::View view;		//!< What the screen is looking at

protected:
	TextureManager * texManager = TextureManager::getInstance();	//!< The texture manager

public:
	LevelSelect() {};
	LevelSelect(float width, float height);		//!< Constructor
	//~Menu();	//!< Deconstructor
	void update(float timestep); //!< Update the menu with give timestep
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw the menu to the render context
	void processKeyPress(sf::Keyboard::Key code);		//!< Decides what to do on key press
	bool getPlay() { return play; }		//!< Returns the play bool
	bool getClose() { return close; }	//!< Returns the close bool
	int getLevel() { return selectedLevel; }	//!< Returns the selected level
	void setPlay(bool Play);		//!< Sets the play bool
	void moveUp();		//!< Move up in the index (text options)
	void moveDown();	//!< Move down in the index (text options)
	void moveLeft();	//!< Move left in the index (text options)
	void moveRight();	//!< Move right in the index (text options)
	void selected();	//!< What to do when an option is selected
};