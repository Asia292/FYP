#pragma once
/*!
\file Lever.h
*/

#include "Sensor.h"
#include "DoorPlat.h"
#include "MovingPlat.h"

/*! \class Lever
\brief Sensor that acts as a lever
*/
class Lever : public Sensor
{
private:
	DoorPlat * door;	//!< The door passed in constructor
	MovingPlat *platform;	//!< The moving platform passed in constructor
	sf::Vector2f pos;
	bool right;

public:
	Lever() {};		//!< Default constructor
	Lever(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size, DoorPlat * Door, bool Right);		//!< Full constructor for a door platform
	Lever(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size, MovingPlat * plat, bool Right);		//!< Full constructor for a moving platform

	virtual void onAction(b2Body * other) override;		//!< Action to do when sensor is triggered
	virtual void offAction(b2Body * other) override {};		//!< Action to do when sensor stops being triggered
};