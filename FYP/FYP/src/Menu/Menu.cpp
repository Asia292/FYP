/*!
\file Menu.cpp
*/

#pragma warning(disable : 4996)

#include "Menu.h"

Menu::Menu(float Width, float Height)
{
	/*
	TO DO
		X Background
		X Text
			X Co-op play
			X Network play
			X Quit
		X Key select or mouse?
			X Key
		X Scene/state transition
			X Quit
			X Level select
	*/
	texManager->setTexture("menu", this);
	setBg();

	play = false;
	network = false;
	networkText = false;
	close = false;
	selectedItemIndex = 0;
	width = Width;
	height = Height;

	view.setSize(sf::Vector2f(1024.f, 800.f));
	view.setCenter(sf::Vector2f(512.f, 400.f));

	font.loadFromFile(".\\assets\\neuropol.ttf");

	menue[0].setFont(font);
	menue[0].setFillColor(sf::Color(100, 32, 188));
	menue[0].setOutlineColor(sf::Color::Black);
	menue[0].setOutlineThickness(3);
	menue[0].setCharacterSize(50);
	menue[0].setString("LOCAL PLAY");
	menue[0].setPosition(sf::Vector2f((width / 2) - 100.f, height / (3 + 1) * 1));
		
	menue[1].setFont(font);
	menue[1].setFillColor(sf::Color(255, 222, 0));
	menue[1].setOutlineColor(sf::Color::Black);
	menue[1].setOutlineThickness(3);
	menue[1].setCharacterSize(50);
	menue[1].setString("NETWORK PLAY");
	menue[1].setPosition(sf::Vector2f((width / 2) - 150.f, height / (4.5 + 1) * 2));

	menue[2].setFont(font);
	menue[2].setFillColor(sf::Color(255, 222, 0));
	menue[2].setOutlineColor(sf::Color::Black);
	menue[2].setOutlineThickness(3);
	menue[2].setCharacterSize(50);
	menue[2].setString("QUIT");
	menue[2].setPosition(sf::Vector2f((width / 2) + 40.f, height / (5 + 1) * 3));
}

/*Menu::~Menu()
{
}*/

void Menu::update(float timestep)
{
	Texture::update(timestep);
	currSprite.setScale(sf::Vector2f(1.0f, 1.0f));

	for (int i = 0; i < 3; i++)
	{
		menue[i].setColor(sf::Color(255, 222, 0));
	}
	menue[selectedItemIndex].setColor(sf::Color(100, 32, 188));

	if (networkText)
	{
		menue[0].setString("HOST");
		menue[0].setPosition(sf::Vector2f((width / 2) + 35.f, height / (3 + 1) * 1));
		menue[1].setString("JOIN");
		menue[1].setPosition(sf::Vector2f((width / 2) + 40.f, height / (4.5 + 1) * 2));
		menue[2].setString("BACK");
		menue[2].setPosition(sf::Vector2f((width / 2) + 30.f, height / (5 + 1) * 3));
	}
	else
	{
		menue[0].setString("LOCAL PLAY");
		menue[0].setPosition(sf::Vector2f((width / 2) - 100.f, height / (3 + 1) * 1));
		menue[1].setString("NETWORK PLAY");
		menue[1].setPosition(sf::Vector2f((width / 2) - 150.f, height / (4.5 + 1) * 2));
		menue[2].setString("QUIT");
		menue[2].setPosition(sf::Vector2f((width / 2) + 40.f, height / (5 + 1) * 3));
	}
}

void Menu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.setView(view);
	target.draw(currSprite, states);
	for (int i = 0; i < 3; i++)
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
		selectedItemIndex--;
	}
}

void Menu::moveDown()
{
	if (selectedItemIndex + 1 < 3)
	{
		selectedItemIndex++;
	}
}

void Menu::selected()
{
	switch (selectedItemIndex)
	{
	case 0:
		if(!networkText)
			play = true;
		else
		{
			network = true;
			host = true;
		}
		break;
	case 1:
		if (!networkText)
		{
			networkText = true;
			selectedItemIndex = 0;
		}
		else
		{
			network = true;
			host = false;
		}
		break;
	case 2:
		if (!networkText)
			close = true;
		else
		{
			networkText = false;
			selectedItemIndex = 0;
		}
		break;
	}
}
