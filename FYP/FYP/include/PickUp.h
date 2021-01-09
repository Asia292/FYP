#pragma once
/*!
\file PickUp.h
*/

#include "Sensor.h"

/*! \class Button
\brief Sensor that acts as a pickup
*/
class PickUp : public Sensor
{
private:
	b2Fixture *fixture;		//!< The body's fixture
	b2Filter filter;		//!< Filter for body collisions
	bool del;		//!< If item should be deleted

public:
	PickUp() {};		//!< Default constructor
	PickUp(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size, int mask);		//!< Full constructor for a door platform
	~PickUp();

	virtual void onAction(b2Body * other) override;		//!< Action to do when sensor is triggered
	virtual void offAction(b2Body * other) override {};		//!< Action to do when sensor stops being triggered

	bool getDel();		//!< Return the delete bool
};