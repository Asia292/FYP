/*!
\file main.cpp
\brief Contains the entry point for the application
*/

#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>
#include "MenuState.h"

void main() /** Entry point for the application */
{
	sf::RenderWindow window(sf::VideoMode(1024, 800), "FYP"); // Open main window

	//Game game;
	State *currState;

	std::stack<State *> states;
	states.push(new MenuState(/*window.getSize().x, window.getSize().y,*/ &states));
	currState = states.top();
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
				currState->processKeyPress(event.key.code);
				//game.processKeyPress(event.key.code);
			}
			if (event.type == sf::Event::KeyReleased)
			{
				currState->processKeyRelease(event.key.code);
				//game.processKeyRelease(event.key.code);
			}
		}

		// Find out how much time has elapsed
		float m_fElapsedTime = clock.getElapsedTime().asSeconds();
		// If a frame has past the update the physics
		if (m_fElapsedTime > fFrameTime)
		{
			if (!states.empty())
			{
				currState = states.top();
				currState->update(m_fElapsedTime);

				if (currState->getQuit())
				{
					delete states.top();
					states.pop();

					if (!states.empty())
						currState = states.top();
					else
						window.close();
				}
			}
			//game.update(m_fElapsedTime);
			clock.restart();
		}

		window.clear(sf::Color(120, 120, 120));

		//window.draw(game);
		window.draw(*currState);

		window.display();
	}
}