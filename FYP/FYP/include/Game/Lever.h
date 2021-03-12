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
	bool right, flipped, revTex;
	std::string reverse, forward;

	TextureManager *texture;

public:
	Lever() {};		//!< Default constructor
	Lever(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size, DoorPlat * Door, bool Right, TextureManager *texMan, const std::string col, const std::string back);		//!< Full constructor for a door platform
	Lever(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size, MovingPlat * plat, bool Right, TextureManager *texMan, const std::string col, const std::string back);		//!< Full constructor for a moving platform

	virtual void onAction(b2Body * other) override;		//!< Action to do when sensor is triggered
	virtual void offAction(b2Body * other) override {};		//!< Action to do when sensor stops being triggered
	void update(float timestep) override;
	bool getTexture() { return revTex; }
	void setTexture(bool tex);
};