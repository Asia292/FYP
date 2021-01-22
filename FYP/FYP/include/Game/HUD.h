#pragma once
/*!
\file HUD.h
*/

/*! \class HUD
\brief Updates and displays information to player - lives, score, time
*/
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

#include "TextureManager.h"

class HUD : public Texture
{
private:
	float eTime;	//<! Elapsed time
	int min;	//!< Minutes of display time
	int sec;	//!< Seconds of display time

	sf::Vector2f timeOffset;		//!< Time position relative to player

	sf::Font passed;	//!< The font passed in
	sf::Text time;		//!< Time text

	
public:
	HUD(TextureManager *texMan, sf::Font &font);	//!< Constructor
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;		//!< Draws everything
	void update(float timestep);		//!< Updates the textures and score, coin count and time text

};