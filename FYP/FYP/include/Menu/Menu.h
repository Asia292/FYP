#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "TextureManager.h"

class Menu : public Texture
{
private:
	bool play;
	bool close;
	int selectedItemIndex;

	sf::Text menue[3];	//!< Text that displays on game over
	sf::Font font;		//!< Font used

	sf::View view;

protected:
	TextureManager * texManager = TextureManager::getInstance();	//!< The texture manager

public:
	Menu() {};
	Menu(float width, float height);		//!< Constructor
	//~Menu();	//!< Deconstructor
	void update(float timestep); //!< Update the game with give timestep
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw the game to the render context
	void processKeyPress(sf::Keyboard::Key code);		//!< Decides what to do on key press
	bool getPlay() { return play; }
	bool getClose() { return close; }
	void setPlay(bool Play);
	void moveUp();
	void moveDown();
	void selected();
};