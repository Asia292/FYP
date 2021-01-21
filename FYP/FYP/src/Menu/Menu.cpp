#include "Menu.h"

Menu::Menu(/*float width, float height*/)
{
	/*
	TO DO
		- Background
		- Text
			- Co-op play
			- Network play
			- Quit
		- Key select or mouse?
		- Scene/state transition
			- Delay/confirmation
	*/

	play = false;
	close = false;
	selectedItemIndex = 0;

	view.setSize(sf::Vector2f(1024.f, 800.f));
	view.setCenter(sf::Vector2f(512.f, 400.f));

	font.loadFromFile(".\\assets\\neuropol.ttf");


	menue[0].setFont(font);
	menue[0].setFillColor(sf::Color::Red);
	menue[0].setOutlineColor(sf::Color::Black);
	menue[0].setOutlineThickness(3);
	menue[0].setCharacterSize(150);
	menue[0].setScale(sf::Vector2f(0.5f, 0.5f));
	menue[0].setString("PLAY");
	menue[0].setPosition(sf::Vector2f(1024 / 2, 800 / (3 + 1) * 1));	//380, 250
		
	menue[1].setFont(font);
	menue[1].setFillColor(sf::Color(35, 179, 241));
	menue[1].setOutlineColor(sf::Color::Black);
	menue[1].setOutlineThickness(3);
	menue[1].setCharacterSize(150);
	menue[1].setScale(sf::Vector2f(0.5f, 0.5f));
	menue[1].setString("QUIT");
	menue[1].setPosition(sf::Vector2f(1024 / 2, 800 / (3 + 1) * 2));	//380, 250
}

/*Menu::~Menu()
{
}*/

void Menu::update(float timestep)
{
}

void Menu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.setView(view);
	for (int i = 0; i < 2; i++)
	{
		target.draw(menue[i]);
		//std::cout << "Drawing: " << menue[i].getString().getData() << std::endl;
	}
}

void Menu::processKeyPress(sf::Keyboard::Key code)
{
	switch (code)
	{
	case sf::Keyboard::Return:
		selected();
		break;
	case sf::Keyboard::Up:
		moveUp();
		break;
	case sf::Keyboard::Down:
		moveDown();
		break;
	}
}

void Menu::setPlay(bool Play)
{
	play = Play;
}

void Menu::moveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menue[selectedItemIndex].setColor(sf::Color(35, 179, 241));
		selectedItemIndex--;
		menue[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::moveDown()
{
	if (selectedItemIndex + 1 < 2)
	{
		menue[selectedItemIndex].setColor(sf::Color(35, 179, 241));
		selectedItemIndex++;
		menue[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::selected()
{
	if (selectedItemIndex == 0)
		play = true;
	else if (selectedItemIndex == 1)
		close = true;
}
