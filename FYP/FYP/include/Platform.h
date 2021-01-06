#pragma once
/*!
\file Platform.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>

/*! \class Platform
\brief Defines base for all platform types
*/
class Platform : public sf::RectangleShape
{
private:
	b2Body * body = nullptr; //!< Box2D body
	const float density = 0.0f; //!< Density of the material - used to give mass
	const float friction = 0.4f; //!< Friction - only friction from movement, not when static
	const float restitution = 0.0f; //!< Restitution - bouncyness of stuff

public:
	Platform() {};		//!< Default constructor
	Platform(b2World * world, const sf::Vector2f& position, const sf::Vector2f &size, const float orientation);		//!< Full constructor
	void setUserData(void* data);		//!< Sets the user data of the body
};