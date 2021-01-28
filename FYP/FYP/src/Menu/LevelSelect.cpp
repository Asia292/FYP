#include "LevelSelect.h"

LevelSelect::LevelSelect(float width, float height)
{
	/*
	TO DO
		X Background
		X Text
			X Each level
				X Level number
				X Score if already done?
		X Boxes to contain each level
		X Move up/down
		- Scroll list with move up/down
		X Scene/state transition
			X Return to menu
			X Load correct level
		X Level preview?
	*/

	texManager->setTexture("levelSelect", this);
	setBg();

	selectedLevel = 0;
	back = 0;
	close = false;
	play = false;

	view.setSize(sf::Vector2f(1024.f, 800.f));
	view.setCenter(sf::Vector2f(512.f, 400.f));

	font.loadFromFile(".\\assets\\neuropol.ttf");

	y = 100.f;
	for (int i = 0; i < MAX_LEVELS; i++)
	{
		backing[i].setSize(sf::Vector2f(500.f, 90.f));
		backing[i].setFillColor(sf::Color(255, 255, 204));
		backing[i].setPosition(sf::Vector2f(30.f, y));
		y += 120.f;

		levels[i].setFont(font);
		levels[i].setFillColor(sf::Color(0, 102, 0));
		levels[i].setOutlineColor(sf::Color::Black);
		levels[i].setOutlineThickness(2);
		levels[i].setCharacterSize(35);
		levels[i].setString("LEVEL " + std::to_string(i + 1));
		levels[i].setPosition(sf::Vector2f(backing[i].getPosition().x + 20.f, backing[i].getPosition().y + 20.f));

		texManager->setTexture("all", &star[i]);
		texManager->getFrames("Empty", &star[i]);

		//lvlScore.score[i] = 0;
		//score[i] = -1;
	}
	backing[0].setFillColor(sf::Color(229, 204, 255));

	menuBox.setSize(sf::Vector2f(200.f, 70.f));
	menuBox.setFillColor(sf::Color(255, 255, 204));
	menuBox.setPosition(sf::Vector2f(775.f, 610.f));

	menu.setFont(font);
	menu.setFillColor(sf::Color(0, 102, 0));
	menu.setOutlineColor(sf::Color::Black);
	menu.setOutlineThickness(2);
	menu.setCharacterSize(30);
	menu.setString("MENU");
	menu.setPosition(sf::Vector2f(menuBox.getPosition().x + 30.f, menuBox.getPosition().y + 15.f));

	texManager->setTexture("onePreview", &preview);
	preview.setBg();
	
}

void LevelSelect::update(float timestep)
{
	Texture::update(timestep);
	currSprite.setScale(sf::Vector2f(1.0f, 1.0f));

	switch (selectedLevel)
	{
	case 0:
		texManager->setTexture("onePreview", &preview);
		break;
	case 1:
		texManager->setTexture("twoPreview", &preview);
		break;
	case 2:
		texManager->setTexture("threePreview", &preview);
		break;
	case 3:
		texManager->setTexture("fourPreview", &preview);
		break;
	case 4:
		texManager->setTexture("fivePreview", &preview);
		break;
	}

	preview.update(timestep);
	preview.setSize(sf::Vector2f(0.4f, 0.4f));
	preview.setPos(sf::Vector2f(570.f, 120.f));

	for (int i = 0; i < MAX_LEVELS; i++)
	{
		//score[i] = lvlScore.score[i];

		star[i].update(timestep);
		switch (score[i])
		{
		case 0:
			texManager->getFrames("Empty", &star[i]);
			break;
		case 1:
			texManager->getFrames("Red", &star[i]);
			break;
		case 2:
			texManager->getFrames("Orange", &star[i]);
			break;
		case 3:
			texManager->getFrames("Green", &star[i]);
			break;
		}
		star[i].setPos(sf::Vector2f(backing[i].getPosition().x + 420.f, backing[i].getPosition().y + 40.f));
	}
}

void LevelSelect::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.setView(view);
	target.draw(currSprite, states);
	for (int i = 0; i < MAX_LEVELS; i++)
	{
		target.draw(backing[i]);
		target.draw(levels[i]);
		target.draw(star[i]);
	}
	target.draw(menuBox);
	target.draw(menu);
	preview.draw(target, states);
}

void LevelSelect::processKeyPress(sf::Keyboard::Key code)
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
	case sf::Keyboard::Right:
		moveRight();
		break;
	case sf::Keyboard::Left:
		moveLeft();
		break;
	}
}

void LevelSelect::setPlay(bool Play)
{
	play = Play;
}

void LevelSelect::moveUp()
{
	if (selectedLevel - 1 >= 0 && back == 0)
	{
		backing[selectedLevel].setFillColor(sf::Color(255, 255, 204));
		selectedLevel--;
		backing[selectedLevel].setFillColor(sf::Color(229, 204, 255));
	}
}

void LevelSelect::moveDown()
{
	if (selectedLevel + 1 < MAX_LEVELS && back == 0)
	{
		backing[selectedLevel].setFillColor(sf::Color(255, 255, 204));
		selectedLevel++;
		backing[selectedLevel].setFillColor(sf::Color(229, 204, 255));
	}
}

void LevelSelect::moveLeft()
{
	if (back - 1 >= 0)
	{
		menuBox.setFillColor(sf::Color(255, 255, 204));
		back--;
		backing[selectedLevel].setFillColor(sf::Color(229, 204, 255));
	}
}

void LevelSelect::moveRight()
{
	if (back + 1 < 2)
	{
		backing[selectedLevel].setFillColor(sf::Color(255, 255, 204));
		back++;
		menuBox.setFillColor(sf::Color(229, 204, 255));
	}
}

void LevelSelect::selected()
{
	if (back == 1)
		close = true;
	else
		play = true;
}
