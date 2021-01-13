#pragma once
/*!
\file Block.h
*/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include "TextureManager.h"

/*! \class Block
\brief Movable object in a block shape
*/
class Block : public Texture
{
private:
	b2Body * body = nullptr; //!< Box2D body
	const float density = 5.0f; //!< Density of the material - used to give mass
	const float friction = 1.0f; //!< Friction - only friction from movement, not when static
	const float restitution = 0.1f; //!< Restitution - bouncyness of stuff

public:
	Block() {};		//!< Default constructor
	Block(b2World * world, const sf::Vector2f& position, const sf::Vector2f &size, const float orientation, TextureManager *texMan);		//!< Full constructor
	void update(float timestep);	//!< Updates entity
	void setUserData(void* data);		//!< Sets the user data of the body
};