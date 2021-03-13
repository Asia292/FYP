#include "LevelSelectState.h"

LevelSelectState::LevelSelectState(float Height, float Width, std::stack<State*>* States, Server * l_server)
{
	states = States;
	quit = false;
	server = l_server;

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
		states->push(new GameState(levelSelect->getLevel(), &(levelSelect->score[levelSelect->getLevel()]), states, server));
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

void LevelSelectState::processNetworkKeyPress(int code, Server* l_server, int id)
{
	levelSelect->processKeyPress((sf::Keyboard::Key)code);

	sf::Packet p;

	if (code != sf::Keyboard::Key::Return)
	{
		StampPacket(PacketType::LvlSelectUpdate, p);
		LevelSelectUpdate update;
		update.currLevel = levelSelect->getLevel();
		update.back = levelSelect->getBack();
		p << update;
	}
	else
	{
		StampPacket(PacketType::StateTransition, p);
		bool up;

		if (levelSelect->getPlay())
			up = true;
		else if (levelSelect->getClose())
			up = false;

		p << up;
	}

	l_server->Broadcast(p);
}

void LevelSelectState::levelSelectUpdate(int lvl, int back)
{
	levelSelect->networkUpdate(lvl, back);
}

void LevelSelectState::stateTransition(bool push)
{
	if (push)
		levelSelect->setPlay(true);
	else
		levelSelect->setClose(true);
}

