#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "TextureManager.h"

class noConnection : public Texture
{
private:
	sf::Text noServer;
	sf::Text ok;
	sf::Font font;

protected:
	TextureManager * texManager = TextureManager::getInstance();	//!< The texture manager

public:
	noConnection();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw the game to the render context
	void update(float timestep);
};