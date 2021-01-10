#pragma once
/*!
\file HomeSensor.h
*/

#include "Sensor.h"
#include "Player.h"

/*! \class HomeSensor
\brief Sensor that changes a bool held in player on contact to say when they have reached home
*/
class HomeSensor : public Sensor
{
public:
	HomeSensor() {};		//!< Default constructor
	HomeSensor(b2World * world, const sf::Vector2f& position, sf::Vector2f& size, Player * play);		//!< Full constructor

	void onAction(b2Body * other);		//!< Action to do when sensor is triggered
	void offAction(b2Body * other);		//!< Action to do when sensor stops being triggered
	Player * player;	//!< The door passed in constructor
};