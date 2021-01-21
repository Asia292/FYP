#pragma once
/*!
\file Game.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "SFMLDebugDraw.h"
#include "ContactListener.h"
#include "Lvl1.h"
#include "HUD.h"
#include <memory>


/*! \class Game
\brief Creates the world and controls the gameplay
*/
class Game : public sf::Drawable
{
private:
	sf::View view; //!< The view maps from physical co-ordinates to rendering co-ordinates
	sf::Vector2f worldSize = sf::Vector2f(14.f, 10.4f); //!< Size of the physical worlds is 8 X 6 metres

	b2World* world = nullptr; //!< Pointer to the Box2D world.  Using pointers as BOX2D has it's own memory management
	const int velIterations = 7; //!< On each update there will be 7 velocity iterations in the physics engine
	const int posIterations = 5; //!< On each update there will be 5 position iterations on each update
	const b2Vec2 gravity = b2Vec2(0.f, 9.81f); //!< Standard earth gravity 

	bool debug; //!< Toggle for debug drawing
	SFMLDebugDraw debugDraw; //!< Box2D debug drawing

	Level *currLevel;	//!< Pointer to the current level
	HUD *hud;			//!< Instance of HUD

	bool lightRight;	//!< If light player should be moving right
	bool lightLeft;		//!< If light player should be moving left
	bool darkRight;		//!< If dark player should be moving right
	bool darkLeft;		//!< If dark player should be moving left

	sf::Text finish;	//!< Text that displays on game over
	sf::Font font;		//!< Font used
	bool over;			//!< If the game is over

protected:
	TextureManager * texManager = TextureManager::getInstance();	//!< The texture manager

public:
	Game() {};		//!< Default constructor
	Game(int level); //!< Full constructor which sets up the game
	~Game(); //!< Destructor which cleans all the pointer memory up
	void update(float timestep); //!< Update the game with give timestep
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw the game to the render context
	void toggleDebug() { debug = !debug; }; //!< Toggle for debug drawing
	void processKeyPress(sf::Keyboard::Key code);		//!< Decides what to do on key press
	void processKeyRelease(sf::Keyboard::Key code);		//!< Decides what to do on key release
	bool getOver() { return over; }

	ContactListener listener;	//!< The contact listener
};