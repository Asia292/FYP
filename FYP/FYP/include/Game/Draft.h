#pragma once
/*!
\file Draft.h
*/

#include "Sensor.h"

/*! \class Draft
\brief Derives from the sensor class. Moves a player in a defined direction when they are in contact with it.
*/
class Draft : public Sensor
{
private:
	float angle;		//!< The angle the draft is facing
	b2Body *player;		//!< The player currently in contact with the draft
public:
	Draft() {};		//!< Default constructor
	Draft(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size, const float orientation);		//!< Full constructor

	virtual void onAction(b2Body * other) override;			//!< Action to do when sensor is triggered
	virtual void offAction(b2Body * other) override;		//!< Action to do when sensor stops being triggered
	virtual void update(float timestep) override;			//!< Updates the entity
};