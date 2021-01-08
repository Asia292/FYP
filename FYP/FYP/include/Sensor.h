#pragma once
/*!
\file Sensor.h
*/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

/*! \class Sensor
\brief Base class for all game sensors
*/
class Sensor : public sf::RectangleShape
{
private:
	b2Body * body = nullptr; //!< Box2D body
	const float density = 1.0f; //!< Density of the material - used to give mass
	const float friction = 0.4f; //!< Friction - only friction from movement, not when static
	const float restitution = 0.1f; //!< Restitution - bouncyness of stuff

public:
	Sensor() {};		//!< Default constructor
	Sensor(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size);		//!< Full constructor

	virtual void onAction(b2Body * other) = 0;		//!< Action to do when sensor is triggered
	virtual void offAction(b2Body * other) = 0;		//!< Action to do when sensor stops being triggered
	void setUserData(void* data);		//!< Sets the user data of the body
};