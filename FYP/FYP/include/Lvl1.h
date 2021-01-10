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
	Player *lightPlayer;		//!< The light player
	Player *darkPlayer;			//!< The dark player

	Hazard *lightHazard;		//!< Hazards to light player
	Hazard *darkHazard;			//!< Hazards to dark player
	Hazard *bothHAzard;			//!< Hazards to both players

	PickUp *lightPickUp[3];		//!< Array of light pickups
	PickUp *darkPickUp[3];		//!< Array of dark pickups

	Block *block;				//!< Movable block

	Floor *floor;				//!< Floor of the game
	b2Vec2 *outline[15];		//!< Array of floor outline vectors

public:
	Lvl1(TextureManager * textMan, b2World * world);		//!< Constructor
	virtual ~Lvl1() override;		//!< Deconstructor
	virtual void update(float timestep) override;		//!< Updates all game elements
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;		//!< Draws all game elements
};