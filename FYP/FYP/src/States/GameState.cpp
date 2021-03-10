#include "GameState.h"

GameState::GameState(int level, int * levelScore, std::stack<State*>* States, Server * l_server)
{
	states = States;
	game = new Game(level, levelScore);
	quit = false;
	server = l_server;
	lvl = level;
	lvlScore = levelScore;
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

	
	if (server != nullptr)
	{
		sf::Packet p;
		StampPacket(PacketType::PlayerUpdate, p);
		PlayerUpdate update;
		float x = game->getCurrLvl()->lightPlayer->body->GetPosition().x;
		float y = game->getCurrLvl()->lightPlayer->body->GetPosition().y - 0.2f;

		update.player = 1;
		update.texture = game->getCurrLvl()->lightPlayer->lightTex;
		update.frame = game->getCurrLvl()->lightPlayer->getFrame();
		update.position = sf::Vector2f(x, y);
		p >> update;
		server->Broadcast(p);


		sf::Packet p2;
		StampPacket(PacketType::PlayerUpdate, p2);
		x = game->getCurrLvl()->darkPlayer->body->GetPosition().x;
		y = game->getCurrLvl()->darkPlayer->body->GetPosition().y - 0.1f;

		update.player = 2;
		update.texture = game->getCurrLvl()->darkPlayer->darkTex;
		update.frame = game->getCurrLvl()->darkPlayer->getFrame();
		update.position = sf::Vector2f(x, y);
		p2 << update;
		server->Broadcast(p2);
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
		StampPacket(PacketType::PlayerUpdate, p);
		PlayerUpdate update;
		float x = game->getCurrLvl()->lightPlayer->body->GetPosition().x;
		float y = game->getCurrLvl()->lightPlayer->body->GetPosition().y - 0.2f;

		update.player = 1;
		update.texture = game->getCurrLvl()->lightPlayer->lightTex;
		update.frame = game->getCurrLvl()->lightPlayer->getFrame();
		update.position = sf::Vector2f(x, y);
		p >> update;


		sf::Packet p2;
		StampPacket(PacketType::PlayerUpdate, p2);
		x = game->getCurrLvl()->darkPlayer->body->GetPosition().x;
		y = game->getCurrLvl()->darkPlayer->body->GetPosition().y - 0.1f;

		update.player = 2;
		update.texture = game->getCurrLvl()->darkPlayer->darkTex;
		update.frame = game->getCurrLvl()->darkPlayer->getFrame();
		update.position = sf::Vector2f(x, y);
		p2 << update;
		l_server->Broadcast(p2);
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
	/*game->setDarkJump(false);
	game->setLightJump(false);
	game->processKeyRelease((sf::Keyboard::Key)code);
	sf::Packet p;
	StampPacket(PacketType::PlayerUpdate, p);
	PlayerUpdate update;
	update.player = 1;
	update.right = game->getLightRight();
	update.left = game->getLightLeft();
	update.jump = game->getLightJump();
	p << update;
	l_server->Broadcast(p);

	sf::Packet p2;
	StampPacket(PacketType::PlayerUpdate, p2);
	update.player = 2;
	update.right = game->getDarkRight();
	update.left = game->getDarkLeft();
	update.jump = game->getDarkJump();
	p2 << update;
	l_server->Broadcast(p2);*/
}

void GameState::playerUpdate(int player, int texture, int frame, sf::Vector2f pos)
{
	game->networkPlayerUpdate(player, texture, frame, pos);
}
