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

//// SENSORS ////
TEST(SensorButton, OnAction)
{
	b2World * world = new b2World(b2Vec2(0, 9.81));
	DoorPlat * door = new DoorPlat(world, sf::Vector2f(-1.5f, 0.f), 0.f);
	MovingPlat *move = new MovingPlat(world, sf::Vector2f(1.5f, 0.f), sf::Vector2f(0.5f, 0.1f), 0.f, sf::Vector2f(1.5f, -1.f));
	Button * button = new Button(world, sf::Vector2f(5, 5), sf::Vector2f(1, 1), door);
	Button * buttonMove = new Button(world, sf::Vector2f(5, 5), sf::Vector2f(1, 1), move);

	int stateBefore = (int)door->state;
	button->onAction(door->door);
	int stateAfter = (int)door->state;

	auto velBefore = move->body->GetLinearVelocity();
	buttonMove->onAction(door->door);
	move->update(2.f);
	auto velAfter = move->body->GetLinearVelocity();

	EXPECT_NE(stateBefore, stateAfter);
	EXPECT_EQ(stateAfter, 3);
	EXPECT_NE(velBefore, velAfter);
}

TEST(SensorButton, OffAction)
{
	b2World * world = new b2World(b2Vec2(0, 9.81));
	DoorPlat * door = new DoorPlat(world, sf::Vector2f(-1.5f, 0.f), 0.f);
	MovingPlat *move = new MovingPlat(world, sf::Vector2f(1.5f, 0.f), sf::Vector2f(0.5f, 0.1f), 0.f, sf::Vector2f(1.5f, -1.f));
	Button * button = new Button(world, sf::Vector2f(5, 5), sf::Vector2f(1, 1), door);
	Button * buttonMove = new Button(world, sf::Vector2f(5, 5), sf::Vector2f(1, 1), move);

	button->onAction(door->door);
	int stateBefore = (int)door->state;
	door->update(2.f);
	button->offAction(door->door);
	int stateAfter = (int)door->state;

	buttonMove->onAction(door->door);
	move->update(2.f);
	auto velBefore = move->body->GetLinearVelocity();
	buttonMove->offAction(door->door);
	move->update(2.f);
	auto velAfter = move->body->GetLinearVelocity();

	EXPECT_NE(stateBefore, stateAfter);
	EXPECT_EQ(stateAfter, 2);
	EXPECT_NE(velBefore, velAfter);
}

/*TEST(SensorLever, OnActionLeft)
{
	b2World * world = new b2World(b2Vec2(0, 9.81));
	DoorPlat * door = new DoorPlat(world, sf::Vector2f(-1.5f, 0.f), 0.f);
	MovingPlat *move = new MovingPlat(world, sf::Vector2f(1.5f, 0.f), sf::Vector2f(0.5f, 0.1f), 0.f, sf::Vector2f(1.5f, -1.f));
	Player * player = new Player(world, sf::Vector2f(1.f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0010, sf::Color::Black);
	Lever * button = new Lever(world, sf::Vector2f(5, 5), sf::Vector2f(1, 1), door);
	Lever * buttonMove = new Lever(world, sf::Vector2f(5, 5), sf::Vector2f(1, 1), move);

	int stateBefore = (int)door->state;
	button->onAction(player->body);
	int stateAfter = (int)door->state;

	auto velBefore = move->body->GetLinearVelocity();
	buttonMove->onAction(player->body);
	move->update(2.f);
	auto velAfter = move->body->GetLinearVelocity();

	EXPECT_NE(stateBefore, stateAfter);
	EXPECT_EQ(stateAfter, 3);
	EXPECT_NE(velBefore, velAfter);
}

TEST(SensorLever, OnActionRight)
{
	b2World * world = new b2World(b2Vec2(0, 9.81));
	DoorPlat * door = new DoorPlat(world, sf::Vector2f(-1.5f, 0.f), 0.f);
	MovingPlat *move = new MovingPlat(world, sf::Vector2f(1.5f, 0.f), sf::Vector2f(0.5f, 0.1f), 0.f, sf::Vector2f(1.5f, -1.f));
	Player * player = new Player(world, sf::Vector2f(8.f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0010, sf::Color::Black);
	Lever * button = new Lever(world, sf::Vector2f(5, 5), sf::Vector2f(1, 1), door);
	Lever * buttonMove = new Lever(world, sf::Vector2f(5, 5), sf::Vector2f(1, 1), move);

	button->onAction(player->body);
	int stateBefore = (int)door->state;
	door->update(2.f);
	button->offAction(player->body);
	int stateAfter = (int)door->state;

	buttonMove->onAction(player->body);
	move->update(2.f);
	auto velBefore = move->body->GetLinearVelocity();
	buttonMove->offAction(player->body);
	move->update(2.f);
	auto velAfter = move->body->GetLinearVelocity();

	EXPECT_NE(stateBefore, stateAfter);
	EXPECT_EQ(stateAfter, 2);
	EXPECT_NE(velBefore, velAfter);
}*/

TEST(SensorPickUp, OnAction)
{
	b2World * world = new b2World(b2Vec2(0, 9.81));
	PickUp *lightPickUp = new PickUp(world, sf::Vector2f(1.2f, 0.5f), sf::Vector2f(0.1f, 0.1f), 0x0100);
	Player * player = new Player(world, sf::Vector2f(8.f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0100, sf::Color::White);

	bool delBefore = lightPickUp->getDel();
	lightPickUp->onAction(player->body);
	bool delAfter = lightPickUp->getDel();

	EXPECT_NE(delBefore, delAfter);
	EXPECT_EQ(delBefore, false);
	EXPECT_EQ(delAfter, true);
}