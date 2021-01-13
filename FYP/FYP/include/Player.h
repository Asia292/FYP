#pragma once
/*!
\file Player.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>

/*! \class Player
\brief Creates and controls the player
*/
class Player : public sf::RectangleShape
{
public:
	b2Body * body = nullptr; //!< Box2D body
	const float density = 1.0f; //!< Density of the material - used to give mass
	const float friction = 1.0f; //!< Friction - only friction from movement, not when static
	const float restitution = 0.1f; //!< Restitution - bouncyness of stuff

	b2Fixture *fixture;		//!< The body's fixture
	b2Filter filter;		//!< Filter for body collisions
	bool grounded;			//!< If the player is grounded
	bool home;				//!< If the player is home
	bool dead;				//!< If the player is dead

public:
	Player() {};		//!< Default constructor
	Player(b2World * world, const sf::Vector2f& position, const sf::Vector2f &size, const float orientation, int cat, sf::Color col);		//!< Full constructor
	void update(float timestep);	//!< Updates entity
	void setUserData(void* data);		//!< Sets the user data of the body

	void moveLeft();	//!< Moves the player left
	void moveRight();	//!< Moves the player right
	void jump();	//!< Makes the player jump
	void idle();	//!< Player is idle/not moving
	void setGrounded(bool ground);		//!< Sets the grounded bool
	void setHome(bool Home);		//!< Sets the home bool
	bool getHome();		//!< Returns the home bool
	void setDead(bool Dead);		//!< Sets the dead bool
	bool getDead();		//!< Returns the dead bool
};