#pragma once
/*!
\file Level.h
*/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <pugixml.hpp>
#include "Server.h"


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
	virtual void update(float timestep, bool server) = 0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
	virtual int score(float time) = 0;
	virtual void networkFrameUpdate(Server * server) = 0;
	virtual void networkUpdate(int object, int index, bool texture, int frame, float angle, sf::Vector2f position) = 0;
};