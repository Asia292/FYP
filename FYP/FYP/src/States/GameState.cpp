#include "GameState.h"

GameState::GameState(int level, int * levelScore, std::stack<State*>* States, Server * l_server)
{
	states = States;
	if (states->size() == 1 && l_server == nullptr)
		game = new Game(level, levelScore, true);
	else
		game = new Game(level, levelScore);
	quit = false;
	server = l_server;
	lvl = level;
	lvlScore = levelScore;
	gameOver = false;
}

GameState::~GameState()
{
	game->~Game();

	delete game;
	game = nullptr;
}

void GameState::update(float timestep)
{
	game->update(timestep);

	if (game->getRetry())
	{
		game->~Game();
		game = new Game(lvl, lvlScore);
	}

	if (game->getBack())
		quit = true;

	
	if (server != nullptr && !gameOver)
	{
		sf::Packet p;
		StampPacket(PacketType::PlayerUpdate, p);
		PlayerUpdate update;
		float x = game->getCurrLvl()->lightPlayer->body->GetPosition().x;
		float y = game->getCurrLvl()->lightPlayer->body->GetPosition().y - 0.2f;

		update.player = 1;
		update.texture = game->getCurrLvl()->lightPlayer->lightTex;
		update.frame = game->getCurrLvl()->lightPlayer->getFrame();
		update.flip = game->getCurrLvl()->lightPlayer->getFlip();
		update.dead = game->getCurrLvl()->lightPlayer->getDead();
		update.position = sf::Vector2f(x, y);
		p << update;
		server->Broadcast(p);


		sf::Packet p2;
		StampPacket(PacketType::PlayerUpdate, p2);
		x = game->getCurrLvl()->darkPlayer->body->GetPosition().x;
		y = game->getCurrLvl()->darkPlayer->body->GetPosition().y - 0.1f;

		update.player = 2;
		update.texture = game->getCurrLvl()->darkPlayer->darkTex;
		update.frame = game->getCurrLvl()->darkPlayer->getFrame();
		update.flip = game->getCurrLvl()->darkPlayer->getFlip();
		update.dead = game->getCurrLvl()->darkPlayer->getDead();
		update.position = sf::Vector2f(x, y);
		p2 << update;
		server->Broadcast(p2);

		if (game->getOver())
			gameOver = true;
	}
	
}

void GameState::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	game->draw(target, states);
}

void GameState::processKeyPress(sf::Keyboard::Key code)
{
	game->processKeyPress(code);
}

void GameState::processNetworkKeyPress(int code, Server* l_server)
{
	game->processKeyPress((sf::Keyboard::Key)code);

	sf::Packet p;

	if (code != sf::Keyboard::Key::Return)
	{
		
	}
	else
	{
		StampPacket(PacketType::StateTransition, p);
		bool up;

		if (game->getRetry())
			up = true;
		else if (game->getBack())
			up = false;

		p << up;
	}

	l_server->Broadcast(p);
}

void GameState::processKeyRelease(sf::Keyboard::Key code)
{
	game->processKeyRelease(code);
}

void GameState::processNetworkKeyRelease(int code, Server* l_server)
{
	game->processKeyRelease((sf::Keyboard::Key)code);
	
}

void GameState::playerUpdate(int player, int texture, int frame, bool flip, bool dead, sf::Vector2f pos)
{
	game->networkPlayerUpdate(player, texture, frame, flip, dead, pos);
}
