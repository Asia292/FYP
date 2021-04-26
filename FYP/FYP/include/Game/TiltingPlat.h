#pragma once
/*!
\file TiltingPlat.h
*/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include "TextureManager.h"

/*! \class TiltingPlat
\brief Platform that tilts according to weight movement, controlled by a revolute joint
*/
class TiltingPlat : public Texture
{
private:
	b2Body * body = nullptr;		//!< Box2D body
	const float density = 1.0f;		//!< Density of the material - used to give mass
	const float friction = 0.1f;	//!< Friction - only friction from movement, not when static
	const float restitution = 0.f;	//!< Restitution - bouncyness of stuff
	b2Body * anchor;				//!< The body that anchors the platform
	b2RevoluteJoint * hinge;		//!< Hinge that allows the platform to rotate
	bool client;					//!< If it was loaded client side or not

public:
	TiltingPlat() {}; //!< Default constructor
	TiltingPlat(b2World * world, sf::Vector2f position, sf::Vector2f size, sf::Vector2f Anchor, float orientation, TextureManager *texMan, const std::string tex, bool onClient = false); // Full constructor
	void update(float timestep);			//!< Updates the platform
	void setUserData(void* data);			//!< Sets the user data of the bodies
	b2Body * getBody() { return body; }		//!< Returns the box2D body
};