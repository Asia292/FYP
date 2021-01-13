#pragma once
/*!
\file Level.h
*/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>


#include "Player.h"
#include "Hazard.h"
#include "DoorPlat.h"
#include "MovingPlat.h"
#include "TiltingPlat.h"
#include "Button.h"
#include "Lever.h"
#include "PickUp.h"
#include "Block.h"
#include "Floor.h"
#include "HomeSensor.h"
#include "TextureManager.h"


/*! \class Level
\brief Base class for all levels
*/
class Level : public Texture
{
public:
	Player *lightPlayer;		//!< The light player
	Player *darkPlayer;			//!< The dark player

	virtual ~Level() = default;
	virtual void update(float timestep) = 0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
};