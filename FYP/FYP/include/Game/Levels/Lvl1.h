#pragma once
/*!
\file Lvl1.h
*/

#include "Level.h"

/*! \class Level
\brief First level of the game
*/
class Lvl1 : public Level
{
protected:

	Hazard *lightHazard;		//!< Hazard to light player
	Hazard *darkHazard;			//!< Hazard to dark player
	Hazard *bothHazard;			//!< Hazard to both players

	PickUp *lightPickUps[3];		//!< Array of light pickups
	PickUp *darkPickUps[3];		//!< Array of dark pickups

	Lever *lever;				//!< A lever
	Button *buttons[2];			//!< Array of buttons
	MovingPlat *platforms[2];	//!< Array of platforms

	Block *block;				//!< Movable block

	Floor *floor;				//!< Floor of the game
	b2Vec2 outline[65];		//!< Array of floor outline vectors

	HomeSensor *lightHome;
	HomeSensor *darkHome;

public:

	Lvl1(TextureManager * textMan, b2World * world);		//!< Constructor
	virtual ~Lvl1() override;		//!< Deconstructor
	virtual void update(float timestep) override;		//!< Updates all game elements
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;		//!< Draws all game elements
};