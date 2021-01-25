#include "LevelSelectState.h"

LevelSelectState::LevelSelectState(float Height, float Width, std::stack<State*>* States)
{
	states = States;
	quit = false;

	levelSelect = new LevelSelect(Width, Height);
}

LevelSelectState::~LevelSelectState()
{
	delete levelSelect;
	levelSelect = nullptr;
}

void LevelSelectState::update(float timestep)
{
	levelSelect->update(timestep);

	if (levelSelect->getPlay())
	{
		states->push(new GameState(levelSelect->getLevel(), &(levelSelect->score[levelSelect->getLevel()]), states));
		levelSelect->setPlay(false);
	}

	if (levelSelect->getClose())
		quit = true;
}

void LevelSelectState::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	levelSelect->draw(target, states);
}

void LevelSelectState::processKeyPress(sf::Keyboard::Key code)
{
	levelSelect->processKeyPress(code);
}

void LevelSelectState::processKeyRelease(sf::Keyboard::Key code)
{
}
