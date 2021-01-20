#pragma once
/*!
\file ContactListener.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Hazard.h"
#include "Sensor.h"
#include "DoorPlat.h"
#include "MovingPlat.h"
#include "TiltingPlat.h"
#include "Floor.h"
#include "Block.h"

/*! \class ContactListener
\brief Defines what happens on collisions
*/
class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);	 //!< Called when contact begins
	void EndContact(b2Contact* contact);	 //!< Called when contact ends
};
