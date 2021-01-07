#pragma once
/*!
\file Button.h
*/

#include "Sensor.h"
#include "DoorPlat.h"

/*! \class Button
\brief Sensor that acts as a button
*/
class Button : public Sensor
{
public:
	Button() {};		//!< Default constructor
	Button(b2World * world, const sf::Vector2f& position, sf::Vector2f& size, DoorPlat * Door);		//!< Full constructor

	virtual void onAction(b2Body * other) override;		//!< Action to do when sensor is triggered
	virtual void offAction(b2Body * other) override;		//!< Action to do when sensor stops being triggered
	DoorPlat * door;	//!< The door passed in constructor
};