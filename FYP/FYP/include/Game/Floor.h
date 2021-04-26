#pragma once
/*!
\file Floor.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>

/*! \class Floor
\brief Creates a chain shape which is used for the floor
*/
class Floor
{
private:
	b2Body * body = nullptr; //!< Box2D body
	const float density = 1.0f; //!< Density of the material - used to give mass
	const float friction = 1.0f; //!< Friction - only friction from movement, not when static
	const float restitution = 0.1f; //!< Restitution - bouncyness of stuff

public:
	Floor(const b2Vec2 *verts, int32 count, b2World * world);	//!< Constructor
	void setUserData(void* data);		//!< Sets the body user data
};