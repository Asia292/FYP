#pragma once
/*!
\file Button.h
*/

#include "Sensor.h"
#include "DoorPlat.h"
#include "MovingPlat.h"

/*! \class Button
\brief Sensor that acts as a button
*/
class Button : public Sensor
{
private:
	DoorPlat * door;	//!< The door passed in constructor
	MovingPlat *platform;	//!< The moving platform passed in constructor

public:
	Button() {};		//!< Default constructor
	Button(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size, DoorPlat * Door, TextureManager *texMan, const std::string col);		//!< Full constructor for a door platform
	Button(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size, MovingPlat * plat, TextureManager *texMan, const std::string col);		//!< Full constructor for a moving platform

	virtual void onAction(b2Body * other) override;		//!< Action to do when sensor is triggered
	virtual void offAction(b2Body * other) override;		//!< Action to do when sensor stops being triggered
	void update(float timestep) override;		//!< Updates the entity
};