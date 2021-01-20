#pragma once
/*!
\file MovingPlat.h
*/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include "TextureManager.h"

/*! \class MovingPlat
\brief Platform that moves to a new position when triggered & moves back
*/
class MovingPlat : public Texture
{
private:
	b2Body * body = nullptr; //!< Box2D body
	const float density = 0.0f; //!< Density of the material - used to give mass
	const float friction = 0.4f; //!< Friction - only friction from movement, not when static
	const float restitution = 0.0f; //!< Restitution - bouncyness of stuff

	b2Vec2 start, end;
	int xMove, yMove;
	bool moveEnd;
	std::string platform, glow;

	TextureManager *texture;

public:
	MovingPlat() {};		//!< Default constructor
	MovingPlat(b2World * world, const sf::Vector2f& position, const sf::Vector2f &size, const float orientation, const sf::Vector2f &End, TextureManager *texMan, const std::string col, const std::string Glow);		//!< Full constructor
	void setUserData(void* data);		//!< Sets the user data of the body
	void moveToEnd();
	void moveToStart();
	void update(float timestep);
};