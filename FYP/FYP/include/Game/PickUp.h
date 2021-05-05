#pragma once
/*!
\file PickUp.h
*/

#include "Sensor.h"

/*! \class PickUp
\brief Derrives from the base sensor class. Creates pickups for players.
*/
class PickUp : public Sensor
{
private:
	b2Fixture *fixture;		//!< The body's fixture
	b2Filter filter;		//!< Filter for body collisions
	bool del;		//!< If item should be deleted

public:
	PickUp() {};		//!< Default constructor
	PickUp(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size, int mask, TextureManager *texMan);		//!< Full constructor for a door platform
	~PickUp();		//!< Deconstructor

	virtual void onAction(b2Body * other) override;		//!< Action to do when sensor is triggered
	virtual void offAction(b2Body * other) override {};		//!< Action to do when sensor stops being triggered
	virtual void update(float timestep) override;

	bool getDel();		//!< Returns the delete bool
	void delTrue() { del = true; }		//!< Sets the delete bool to true - only used for network update
};