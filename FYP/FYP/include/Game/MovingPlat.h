#pragma once
/*!
\file MovingPlat.h
*/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include "TextureManager.h"

/*! \class MovingPlat
\brief Platform that moves from one defined point to another when triggered
*/
class MovingPlat : public Texture
{
private:
	b2Body * body = nullptr; //!< Box2D body
	const float density = 0.0f; //!< Density of the material - used to give mass
	const float friction = 0.4f; //!< Friction - only friction from movement, not when static
	const float restitution = 0.0f; //!< Restitution - bouncyness of stuff

	b2Vec2 start, end;				//!< The start and end positions of the paltform
	int xMove, yMove;				//!< How much the platform should move in X and Y
	bool moveEnd;					//!< If the platform should move towards the end position
	bool glowTex;					//!< If the glow texture is currently being used
	std::string platform, glow;		//!< The names of the normal and glow textures
	bool client;					//!< If it is loaded client side or not

	TextureManager *texture;		//!< A pointer to the texture manager

public:
	MovingPlat() {};		//!< Default constructor
	MovingPlat(b2World * world, const sf::Vector2f& position, const sf::Vector2f &size, const float orientation, const sf::Vector2f &End, TextureManager *texMan, const std::string col, const std::string Glow, bool onClient = false);		//!< Full constructor
	void setUserData(void* data);			//!< Sets the user data of the body
	void moveToEnd();						//!< Moves the platform to the end position
	void moveToStart();						//!< Moves the platform to the start position
	void update(float timestep);			//!< Updates the entity
	b2Body * getBody() { return body; }		//!< Returns the box2D body - onyl for network updates
	bool getGlow() { return glowTex; }		//!< Returns the glowTex bool - onyl for network updates
	void setTexture(bool tex);				//!< Sets the texture to be used - onyl for network updates
};