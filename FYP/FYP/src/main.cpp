/*!
\file main.cpp
\brief Contains the entry point for the application
*/

#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>
#include "Game.h"

void main() /** Entry point for the application */
{
	sf::RenderWindow window(sf::VideoMode(1024, 800), "CW Starter"); // Open main window

	Game game;

	float fFrameTime = 1.f / 60.f;

	// Start a clock to provide time for the physics
	sf::Clock clock;

	// Run a game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// window closed button pressed
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				game.processKeyPress(event.key.code);
			}
		}

		// Find out how much time has elapsed
		float m_fElapsedTime = clock.getElapsedTime().asSeconds();
		// If a frame has past the update the physics
		if (m_fElapsedTime > fFrameTime)
		{
			game.update(m_fElapsedTime);
			clock.restart();
		}

		window.clear(sf::Color(120, 120, 120));

		window.draw(game);

		window.display();
	}
}