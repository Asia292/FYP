#pragma once
/*!
\file Lvl1.h
*/

#include "LevelOld.h"

/*! \class Level
\brief Second level of the game
*/
class Lvl2 : public LevelOld
{
protected:
	Hazard *hazards[6];
	TiltingPlat *tilt[2];
	DoorPlat *slide[2];
	Button *buttons[4];

	PickUp *lightPickUps[8];
	PickUp *darkPickUps[8];

	HomeSensor *lightHome;
	HomeSensor *darkHome;

	Floor *floors[4];				//!< Floor of the game
	b2Vec2 outlineOne[38];		//!< Array of floor outline vectors
	b2Vec2 outlineTwo[11];
	b2Vec2 outlineThree[7];
	b2Vec2 outlineFour[7];

	bool lEmpty, dEmpty;
	bool client;
	sf::Vector2f doorPosBefore[2];
	float tiltAngleBefore[2];
	bool lightHomeBefore;
	bool darkHomeBefore;

	pugi::xml_document doc;

public:

	Lvl2(TextureManager * textMan, b2World * world, bool onClient);		//!< Constructor
	virtual ~Lvl2() override;		//!< Deconstructor
	virtual void update(float timestep, bool server) override;		//!< Updates all game elements
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;		//!< Draws all game elements
	virtual int score(float time) override;		//!< Calculates level score
	virtual void networkFrameUpdate(Server * server) override;
	virtual void networkUpdate(int object, int index, bool texture, int frame, float angle, sf::Vector2f position) override;
};