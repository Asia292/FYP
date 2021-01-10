#pragma once
/*!
\file Game.h
*/

/*! \class Game
\brief Creates the world and controls the gameplay
*/
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "SFMLDebugDraw.h"
#include "ContactListener.h"
#include "PlatTemp.h"
#include "Player.h"
#include "Hazard.h"
#include "DoorPlat.h"
#include "MovingPlat.h"
#include "TiltingPlat.h"
#include "Button.h"
#include "Lever.h"
#include "PickUp.h"
#include "Block.h"
#include "TextureManager.h"
#include <memory>


class Game : public sf::Drawable
{
private:
	sf::View view; //!< The view maps from physical co-ordinates to rendering co-ordinates
	sf::Vector2f worldSize = sf::Vector2f(8.f, 6.f); //!< Size of the physical worlds is 8 X 6 metres

	b2World* world = nullptr; //!< Pointer to the Box2D world.  Using pointers as BOX2D has it's own memory management
	const int velIterations = 7; //!< On each update there will be 7 velocity iterations in the physics engine
	const int posIterations = 5; //!< On each update there will be 5 position iterations on each update
	const b2Vec2 gravity = b2Vec2(0.f, 9.81f); //!< Standard earth gravity 

	bool debug; //!< Toggle for debug drawing
	SFMLDebugDraw debugDraw; //!< Box2D debug drawing

	PlatTemp *platform[1];		//!< Array of platforms
	Hazard *darkHazards[1];		//!< Array of hazards to the dark player
	Hazard *lightHazards[1];	//!< Array of hazards to the light player
	Hazard *bothHazards[1];		//!< Array of hazards to both players
	PickUp *lightPickUps[1];	//!< Array of pickups for light player
	Block *blocks[1];			//!< Array of movable blocks
	DoorPlat *door;
	Lever *button;
	MovingPlat *move;
	TiltingPlat *tilt;

	Player *lightPlayer;		//!< The light player
	Player *darkPlayer;			//!< The dark player

	bool lightRight;	//!< If light player should be moving right
	bool lightLeft;		//!< If light player should be moving left
	bool darkRight;		//!< If dark player should be moving right
	bool darkLeft;		//!< If dark player should be moving left

protected:
	TextureManager * texManager = TextureManager::getInstance();

public:
	Game(); //!< Constructor which sets up the game
	~Game(); //!< Destructor which cleans all the pointer memory up
	void update(float timestep); //!< Update the game with give timestep
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw the game to the render context
	void toggleDebug() { debug = !debug; }; //!< Toggle for debug drawing
	void processKeyPress(sf::Keyboard::Key code);		//!< Decides what to do on key press
	void processKeyRelease(sf::Keyboard::Key code);		//!< Decides what to do on key release

	ContactListener listener;	//!< The contact listener
};