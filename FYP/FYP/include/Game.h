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
#include <memory>


class Game : public sf::Drawable
{
private:
	sf::View view; //!< The view maps from physical co-ordinates to rendering co-ordinates
	sf::Vector2f worldSize = sf::Vector2f(4.f, 3.f); //!< Size of the physical worlds is 4 X 3 metres
	sf::Vector2f playerPos;		//!< Position of the player

	b2World* world = nullptr; //!< Pointer to the Box2D world.  Using pointers as BOX2D has it's own memory management
	const int velIterations = 7; //!< On each update there will be 7 velocity iterations in the physics engine
	const int posIterations = 5; //!< On each update there will be 5 position iterations on each update
	const b2Vec2 gravity = b2Vec2(0.f, 9.81f); //!< Standard earth gravity 

	
	bool debug; //!< Toggle for debug drawing
	SFMLDebugDraw debugDraw; //!< Box2D debug drawing

public:
	Game(); //!< Constructor which sets up the game
	~Game(); //!< Destructor which cleans all the pointer memory up
	void update(float timestep); //!< Update the game with give timestep
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw the game to the render context
	void toggleDebug() { debug = !debug; }; //!< Toggle for debug drawing
	void processKeyPress(sf::Keyboard::Key code);		//!< Decides what to do on key press
};