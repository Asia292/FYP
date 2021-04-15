#pragma once
/*!
\file Level.h
*/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <pugixml.hpp>
#include "Server.h"


#include "Player.h"
#include "Hazard.h"
#include "DoorPlat.h"
#include "MovingPlat.h"
#include "TiltingPlat.h"
#include "Button.h"
#include "Lever.h"
#include "PickUp.h"
#include "Block.h"
#include "Draft.h"
#include "Floor.h"
#include "HomeSensor.h"
#include "TextureManager.h"


/*! \class Level
\brief Base class for all levels
*/
class Level : public Texture
{
private:
	pugi::xml_document doc;
	pugi::xml_node lvl;
	pugi::xml_node curr;
	pugi::xml_node pos;
	pugi::xml_node size;
	Texture cover;
	float lvlTime;

protected:
	std::vector<PickUp*> lightPickUps;
	std::vector<PickUp*> darkPickUps;
	std::vector<Hazard*> hazards;
	std::vector<MovingPlat*> movingPlats;
	std::vector<DoorPlat*> doorPlats;
	std::vector<TiltingPlat*> tiltPlats;
	std::vector<Lever*> levers;
	std::vector<Button*> buttons;
	std::vector<Block*> blocks;
	std::vector<Draft*> drafts;

	HomeSensor *lightHome;
	HomeSensor *darkHome;

	std::vector<Floor*> floors;
	std::vector<b2Vec2> outline;

	bool lEmpty, dEmpty;
	bool client;
	std::vector<b2Vec2> movePlatPosBefore;
	std::vector<sf::Vector2f> doorPosBefore;
	std::vector<float> tiltAngleBefore;
	std::vector<int> leverFrameBefore;
	std::vector<b2Vec2> blockPosBefore;
	bool lightHomeBefore;
	bool darkHomeBefore;


public:
	Player *lightPlayer;		//!< The light player
	Player *darkPlayer;			//!< The dark player

	Level(TextureManager * textMan, b2World * world, int level, bool onClient);		//!< Constructor
	~Level();
	void update(float timestep, bool server);
	void draw(sf::RenderTarget &target, sf::RenderStates states);
	int score(float time);
	void networkFrameUpdate(Server * server);
	void networkUpdate(int object, int index, bool texture, int frame, float angle, sf::Vector2f position);
};