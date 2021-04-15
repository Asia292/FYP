#pragma once
/*!
\file Lvl1.h
*/

#include "LevelOld.h"

/*! \class Level
\brief First level of the game
*/
class Lvl1 : public LevelOld
{
protected:
	//Hazard *hazards[3];
	std::vector<Hazard*> hazards;

	//PickUp *lightPickUps[3];		//!< Array of light pickups
	//PickUp *darkPickUps[3];		//!< Array of dark pickups
	std::vector<PickUp*> lightPickUps;
	std::vector<PickUp*> darkPickUps;

	//Lever *lever;				//!< A lever
	//Button *buttons[2];			//!< Array of buttons
	//MovingPlat *platforms[2];	//!< Array of platforms
	std::vector<Lever*> levers;
	std::vector<Button*> buttons;
	std::vector<MovingPlat*> movingPlats;

	//Block *block;				//!< Movable block
	std::vector<Block*> blocks;

	//Floor *floor;				//!< Floor of the game
	//b2Vec2 outline[65];		//!< Array of floor outline vectors
	std::vector<Floor*> floors;
	std::vector<b2Vec2> outline;

	HomeSensor *lightHome;
	HomeSensor *darkHome;

	bool lEmpty, dEmpty;
	bool client;
	std::vector<int> leverFrameBefore;
	std::vector<b2Vec2> movePlatPosBefore;
	std::vector<b2Vec2> blockPosBefore;
	bool lightHomeBefore;
	bool darkHomeBefore;

	pugi::xml_document doc;

public:

	Lvl1(TextureManager * textMan, b2World * world, bool onClient);		//!< Constructor
	virtual ~Lvl1() override;		//!< Deconstructor
	virtual void update(float timestep, bool server) override;		//!< Updates all game elements
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;		//!< Draws all game elements
	virtual int score(float time) override;		//!< Calculates level score
	virtual void networkFrameUpdate(Server * server) override;
	virtual void networkUpdate(int object, int index, bool texture, int frame, float angle, sf::Vector2f position) override;
};