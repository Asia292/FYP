#pragma once
#include <gtest/gtest.h>

#define private public
#define protected public
#include "game.h"

TEST(GameInternals, ToggleDebug)
{
	Game game;

	bool debugBefore = game.debug;
	game.toggleDebug();
	bool debugAfter = game.debug;

	EXPECT_NE(debugBefore, debugAfter);
}

TEST(GameInternals, Tab)
{
	Game game;

	bool debugBefore = game.debug;
	sf::Keyboard::Key key = sf::Keyboard::Tab;
	game.processKeyPress(key);
	bool debugAfter = game.debug;

	EXPECT_NE(debugBefore, debugAfter);
}

//// PLAYER FUNCTIONS ////
TEST(LightPlayerFunctions, PlayerLeft)
{
	Game game;
	b2World * world = new b2World(b2Vec2(0, 9.81));
	Player * player = new Player(world, sf::Vector2f(0.5f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0100, sf::Color::White);

	float velBefore = player->body->GetLinearVelocity().x;
	player->moveLeft();
	float velAfter = player->body->GetLinearVelocity().x;

	float velKeyBefore = game.lightPlayer->body->GetLinearVelocity().x;
	sf::Keyboard::Key key = sf::Keyboard::A;
	game.processKeyPress(key);
	game.update(0.5f);
	float velKeyAfter = game.lightPlayer->body->GetLinearVelocity().x;

	EXPECT_GT(velBefore, velAfter);
	EXPECT_GT(velKeyBefore, velKeyAfter);
}

TEST(LightPlayerFunctions, PlayerRight)
{
	Game game;
	b2World * world = new b2World(b2Vec2(0, 9.81));
	Player * player = new Player(world, sf::Vector2f(0.5f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0100, sf::Color::White);

	float velBefore = player->body->GetLinearVelocity().x;
	player->moveRight();
	float velAfter = player->body->GetLinearVelocity().x;

	float velKeyBefore = game.lightPlayer->body->GetLinearVelocity().x;
	sf::Keyboard::Key key = sf::Keyboard::D;
	game.processKeyPress(key);
	game.update(0.5f);
	float velKeyAfter = game.lightPlayer->body->GetLinearVelocity().x;

	EXPECT_LT(velBefore, velAfter);
	EXPECT_LT(velKeyBefore, velKeyAfter);
}

TEST(LightPlayerFunctions, PlayerJump)
{
	Game game;
	b2World * world = new b2World(b2Vec2(0, 9.81));
	Player * player = new Player(world, sf::Vector2f(0.5f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0100, sf::Color::White);

	float velBefore = player->body->GetLinearVelocity().y;
	player->jump();
	float velAfter = player->body->GetLinearVelocity().y;

	float velKeyBefore = game.lightPlayer->body->GetLinearVelocity().y;
	sf::Keyboard::Key key = sf::Keyboard::W;
	game.processKeyPress(key);
	float velKeyAfter = game.lightPlayer->body->GetLinearVelocity().y;

	EXPECT_GT(velBefore, velAfter);
	EXPECT_GT(velKeyBefore, velKeyAfter);
}

TEST(DarkPlayerFunctions, PlayerLeft)
{
	Game game;
	b2World * world = new b2World(b2Vec2(0, 9.81));
	Player * player = new Player(world, sf::Vector2f(1.f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0010, sf::Color::Black);

	float velBefore = player->body->GetLinearVelocity().x;
	player->moveLeft();
	float velAfter = player->body->GetLinearVelocity().x;

	float velKeyBefore = game.darkPlayer->body->GetLinearVelocity().x;
	sf::Keyboard::Key key = sf::Keyboard::Left;
	game.processKeyPress(key);
	game.update(0.5f);
	float velKeyAfter = game.darkPlayer->body->GetLinearVelocity().x;

	EXPECT_GT(velBefore, velAfter);
	EXPECT_GT(velKeyBefore, velKeyAfter);
}

TEST(DarkPlayerFunctions, PlayerRight)
{
	Game game;
	b2World * world = new b2World(b2Vec2(0, 9.81));
	Player * player = new Player(world, sf::Vector2f(1.f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0010, sf::Color::Black);

	float velBefore = player->body->GetLinearVelocity().x;
	player->moveRight();
	float velAfter = player->body->GetLinearVelocity().x;

	float velKeyBefore = game.darkPlayer->body->GetLinearVelocity().x;
	sf::Keyboard::Key key = sf::Keyboard::Right;
	game.processKeyPress(key);
	game.update(0.5f);
	float velKeyAfter = game.darkPlayer->body->GetLinearVelocity().x;

	EXPECT_LT(velBefore, velAfter);
	EXPECT_LT(velKeyBefore, velKeyAfter);
}

TEST(DarkPlayerFunctions, PlayerJump)
{
	Game game;
	b2World * world = new b2World(b2Vec2(0, 9.81));
	Player * player = new Player(world, sf::Vector2f(1.f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0010, sf::Color::Black);

	float velBefore = player->body->GetLinearVelocity().y;
	player->jump();
	float velAfter = player->body->GetLinearVelocity().y;

	float velKeyBefore = game.darkPlayer->body->GetLinearVelocity().y;
	sf::Keyboard::Key key = sf::Keyboard::Up;
	game.processKeyPress(key);
	float velKeyAfter = game.darkPlayer->body->GetLinearVelocity().y;

	EXPECT_GT(velBefore, velAfter);
	EXPECT_GT(velKeyBefore, velKeyAfter);
}