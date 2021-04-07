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
	b2Body * body = nullptr; //!< Box2D body
	const float density = 1.0f; //!< Density of the material - used to give mass
	const float friction = 0.1f; //!< Friction - only friction from movement, not when static
	const float restitution = 0.f; //!< Restitution - bouncyness of stuff
	b2Body * anchor;
	b2RevoluteJoint * hinge;
	bool client;

public:
	TiltingPlat() {}; //!< Default constructor
	TiltingPlat(b2World * world, sf::Vector2f position, sf::Vector2f size, sf::Vector2f Anchor, float orientation, TextureManager *texMan, const std::string tex, bool onClient = false); // Full constructor
	//void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< Draw door
	void update(float timestep);
	void setUserData(void* data);		//!< Sets the user data of the bodies
	b2Body * getBody() { return body; }
};