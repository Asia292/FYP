#include "MenuState.h"

MenuState::MenuState(/*float Height, float Width,*/ std::stack<State *>* States)
{
	states = States;
	quit = false;
	//menu = new Menu(Width, Height);
}

MenuState::~MenuState()
{
	//menu.~Menu();

	/*delete menu;
	menu = nullptr;*/
}

void MenuState::update(float timestep)
{
	menu.update(timestep);

	if (menu.getPlay())
	{
		states->push(new GameState(1, states));
		menu.setPlay(false);
	}
	
	if (menu.getClose())
		quit = true;
}

void MenuState::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	menu.draw(target, states);
}

void MenuState::processKeyPress(sf::Keyboard::Key code)
{
	menu.processKeyPress(code);
}

void MenuState::processKeyRelease(sf::Keyboard::Key code)
{
}
