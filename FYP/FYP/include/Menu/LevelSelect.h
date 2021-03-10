#pragma once
/*!
\file LevelSelect.h
*/

#include <SFML/Graphics.hpp>
#include <iostream>

#include "TextureManager.h"

#define MAX_LEVELS 5

/*! \class LevelSelect
\brief The level select screen
*/
class LevelSelect : public Texture
{
private:
	bool close;				//!< If level select screen should close
	bool play;				//!< If a level has been selected to play
	int selectedLevel;		//!< The level selected to play
	int back;				//!< To return to main menu or traverse levels
	float y;				//!< Y offset of level boxes

	sf::RectangleShape menuBox;					//!< Backing for the menu "button"
	sf::RectangleShape backing[MAX_LEVELS];		//!< Backing for the levels
	Texture preview;							//!< Preview of the hovered level
	Texture star[MAX_LEVELS];					//!< Star to indicate score for each level
	sf::Text menu;								//!< Menu text
	sf::Text levels[MAX_LEVELS];				//!< Level text
	sf::Font font;								//!< Font used

	sf::View view;		//!< What the screen is looking at

protected:
	TextureManager * texManager = TextureManager::getInstance();	//!< The texture manager

public:
	LevelSelect() {};		//!< Default constructor
	LevelSelect(float width, float height);		//!< Full constructor
	//~Menu();	//!< Deconstructor
	void update(float timestep); //!< Update the menu with give timestep
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw the menu to the render context
	void processKeyPress(sf::Keyboard::Key code);		//!< Decides what to do on key press
	bool getPlay() { return play; }		//!< Returns the play bool
	bool getClose() { return close; }	//!< Returns the close bool
	int getLevel() { return selectedLevel; }	//!< Returns the selected level
	int getBack() { return back; }
	void networkUpdate(int lvl, int Back);
	void setPlay(bool Play) { play = Play; }		//!< Sets the play bool
	void setClose(bool quit) { close = quit; }
	void moveUp();		//!< Move up in the index (text options)
	void moveDown();	//!< Move down in the index (text options)
	void moveLeft();	//!< Move left in the index (text options)
	void moveRight();	//!< Move right in the index (text options)
	void selected();	//!< What to do when an option is selected

	int score[MAX_LEVELS];		//!< Array of score for each level
};