#pragma once
/*!
\file noConnection.h
*/

#include <SFML/Graphics.hpp>
#include <iostream>

#include "TextureManager.h"

/*! \class noConnection
\brief Creates the "no connection" screen, informing players there is no server to connect to
*/
class noConnection : public Texture
{
private:
	sf::Text noServer;		//!< Text which states there is no server
	sf::Text ok;			//!< Okay text to return to menu
	sf::Font font;			//!< The font used

protected:
	TextureManager * texManager = TextureManager::getInstance();	//!< The texture manager

public:
	noConnection();		//!< Constructor
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draws the scene to the render context
	void update(float timestep);		//!< Updates the textures in the scene
};