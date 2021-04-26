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


/*! \class Level
\brief Base class for all levels
*/
class Level : public Texture
{
private:
	pugi::xml_document doc;		//!< The XML document
	pugi::xml_node lvl;			//!< The level loaded from the XML
	pugi::xml_node curr;		//!< The current node loaded from the XML
	pugi::xml_node pos;			//!< The position of the current node loaded from the XML
	pugi::xml_node size;		//!< The size of the current node loaded from the XML
	Texture cover;				//!< The cover for the level
	float lvlTime;				//!< The time needed to get max score on the level

	std::vector<PickUp*> lightPickUps;			//!< Vector of light pick ups
	std::vector<PickUp*> darkPickUps;			//!< vecotr of dark pick ups
	std::vector<Hazard*> hazards;				//!< Vector of hazards
	std::vector<MovingPlat*> movingPlats;		//!< Vector of moving platforms
	std::vector<DoorPlat*> doorPlats;			//!< Vector of door/sliding platforms
	std::vector<TiltingPlat*> tiltPlats;		//!< Vector of tilting platforms
	std::vector<Lever*> levers;					//!< Vector of levers
	std::vector<Button*> buttons;				//!< Vector of buttons
	std::vector<Block*> blocks;					//!< Vector of blocks
	std::vector<Draft*> drafts;					//!< Vector of drafts

	HomeSensor *lightHome;						//!< The light player home sensor
	HomeSensor *darkHome;						//!< The dark player home sensor

	std::vector<Floor*> floors;					//!< Vector of floors
	std::vector<b2Vec2> outline;				//!< Vector of outline coordinates

	bool lEmpty, dEmpty;						//!< If light or dakr pick up vectors are empty
	bool client;								//!< If the level is loaded client side
	std::vector<b2Vec2> movePlatPosBefore;		//!< Vector of moving platform positions - used in network updates to check if it changed
	std::vector<sf::Vector2f> doorPosBefore;	//!< Vector of door/sliding platform positions before - used in network updates to check if it changed
	std::vector<float> tiltAngleBefore;			//!< Vector of tilting platform angles before - used in network updates to check if it changed
	std::vector<int> leverFrameBefore;			//!< Vector of lever frame numbers before - used in network updates to check if it changed
	std::vector<b2Vec2> blockPosBefore;			//!< Vector of block positions - used in network updates to check if it changed
	bool lightHomeBefore;						//!< If the light player is home - used in network updates to check if it changed
	bool darkHomeBefore;						//!< If the dakr player is home - used in network updates to check if it changed


public:
	Player *lightPlayer;		//!< The light player
	Player *darkPlayer;			//!< The dark player

	Level(TextureManager * textMan, b2World * world, int level, bool onClient);		//!< Constructor
	~Level();		//!< Deconstructor
	void update(float timestep, bool server);		//!< Updates elements depending on being server side or not
	void draw(sf::RenderTarget &target, sf::RenderStates states);		//!< Draws all game elements
	int score(float time);		//!< Calculates the levels score upon completion
	void networkFrameUpdate(Server * server);		//!< Only for networking - checks if any variables have changed and sends an update packet
	void networkUpdate(int object, int index, bool texture, int frame, float angle, sf::Vector2f position);		//!< Updates elements based on network update packets
};