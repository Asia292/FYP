#pragma once
/*!
\file Hazard.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>

/*! \class Hazard
\brief Defines the box2d hazard body
*/
class Hazard : public sf::RectangleShape
{
protected:
	b2Body * body = nullptr; //!< Box2D body
	const float density = 1.0f; //!< Density of the material - used to give mass
	const float friction = 0.4f; //!< Friction - only friction from movement, not when static
	const float restitution = 0.0f; //!< Restitution - bouncyness of stuff

	b2Fixture *fixture;		//!< The body's fixture
	b2Filter filter;		//!< Filter for body collisions

public:
	Hazard() {};	//!< Default constructor
	Hazard(b2World * world, const sf::Vector2f& position, const sf::Vector2f &size, const float orientation, int mask, sf::Color col);		//!< Full constructor

	void setUserData(void* data);		//!< Sets the user data of the body
};