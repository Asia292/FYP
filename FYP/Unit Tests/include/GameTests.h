#pragma once
#include <gtest/gtest.h>

#define private public
#define protected public
#include "Game.h"

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
	int score = 1;
	Game game(0, &score);
	TextureManager * texManager = TextureManager::getInstance();
	b2World * world = new b2World(b2Vec2(0, 9.81));
	Player * player = new Player(world, sf::Vector2f(0.5f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0100, texManager);

	float velBefore = player->body->GetLinearVelocity().x;
	player->moveLeft();
	float velAfter = player->body->GetLinearVelocity().x;

	float velKeyBefore = game.currLevel->lightPlayer->body->GetLinearVelocity().x;
	sf::Keyboard::Key key = sf::Keyboard::A;
	game.processKeyPress(key);
	game.update(0.5f);
	float velKeyAfter = game.currLevel->lightPlayer->body->GetLinearVelocity().x;

	EXPECT_GT(velBefore, velAfter);
	EXPECT_GT(velKeyBefore, velKeyAfter);
}

TEST(LightPlayerFunctions, PlayerRight)
{
	int score = 1;
	Game game(0, &score);
	TextureManager * texManager = TextureManager::getInstance();
	b2World * world = new b2World(b2Vec2(0, 9.81));
	Player * player = new Player(world, sf::Vector2f(0.5f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0100, texManager);

	float velBefore = player->body->GetLinearVelocity().x;
	player->moveRight();
	float velAfter = player->body->GetLinearVelocity().x;

	float velKeyBefore = game.currLevel->lightPlayer->body->GetLinearVelocity().x;
	sf::Keyboard::Key key = sf::Keyboard::D;
	game.processKeyPress(key);
	game.update(0.5f);
	float velKeyAfter = game.currLevel->lightPlayer->body->GetLinearVelocity().x;

	EXPECT_LT(velBefore, velAfter);
	EXPECT_LT(velKeyBefore, velKeyAfter);
}

TEST(LightPlayerFunctions, PlayerJumpGrounded)
{
	int score = 1;
	Game game(0, &score);
	TextureManager * texManager = TextureManager::getInstance();
	b2World * world = new b2World(b2Vec2(0, 9.81));
	Player * player = new Player(world, sf::Vector2f(0.5f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0100, texManager);

	game.currLevel->lightPlayer->setGrounded(true);
	player->setGrounded(true);

	float velBefore = player->body->GetLinearVelocity().y;
	player->jump();
	float velAfter = player->body->GetLinearVelocity().y;

	float velKeyBefore = game.currLevel->lightPlayer->body->GetLinearVelocity().y;
	sf::Keyboard::Key key = sf::Keyboard::W;
	game.processKeyPress(key);
	float velKeyAfter = game.currLevel->lightPlayer->body->GetLinearVelocity().y;

	EXPECT_GT(velBefore, velAfter);
	EXPECT_GT(velKeyBefore, velKeyAfter);
}

TEST(DarkPlayerFunctions, PlayerLeft)
{
	int score = 1;
	Game game(0, &score);
	TextureManager * texManager = TextureManager::getInstance();
	b2World * world = new b2World(b2Vec2(0, 9.81));
	Player * player = new Player(world, sf::Vector2f(1.f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0010, texManager);

	float velBefore = player->body->GetLinearVelocity().x;
	player->moveLeft();
	float velAfter = player->body->GetLinearVelocity().x;

	float velKeyBefore = game.currLevel->darkPlayer->body->GetLinearVelocity().x;
	sf::Keyboard::Key key = sf::Keyboard::Left;
	game.processKeyPress(key);
	game.update(0.5f);
	float velKeyAfter = game.currLevel->darkPlayer->body->GetLinearVelocity().x;

	EXPECT_GT(velBefore, velAfter);
	EXPECT_GT(velKeyBefore, velKeyAfter);
}

TEST(DarkPlayerFunctions, PlayerRight)
{
	int score = 1;
	Game game(0, &score);
	TextureManager * texManager = TextureManager::getInstance();
	b2World * world = new b2World(b2Vec2(0, 9.81));
	Player * player = new Player(world, sf::Vector2f(1.f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0010, texManager);

	float velBefore = player->body->GetLinearVelocity().x;
	player->moveRight();
	float velAfter = player->body->GetLinearVelocity().x;

	float velKeyBefore = game.currLevel->darkPlayer->body->GetLinearVelocity().x;
	sf::Keyboard::Key key = sf::Keyboard::Right;
	game.processKeyPress(key);
	game.update(0.5f);
	float velKeyAfter = game.currLevel->darkPlayer->body->GetLinearVelocity().x;

	EXPECT_LT(velBefore, velAfter);
	EXPECT_LT(velKeyBefore, velKeyAfter);
}

TEST(DarkPlayerFunctions, PlayerJumpGrounded)
{
	int score = 1;
	Game game(0, &score);
	TextureManager * texManager = TextureManager::getInstance();
	b2World * world = new b2World(b2Vec2(0, 9.81));
	Player * player = new Player(world, sf::Vector2f(1.f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0010, texManager);

	game.currLevel->darkPlayer->setGrounded(true);
	player->setGrounded(true);

	float velBefore = player->body->GetLinearVelocity().y;
	player->jump();
	float velAfter = player->body->GetLinearVelocity().y;

	float velKeyBefore = game.currLevel->darkPlayer->body->GetLinearVelocity().y;
	sf::Keyboard::Key key = sf::Keyboard::Up;
	game.processKeyPress(key);
	float velKeyAfter = game.currLevel->darkPlayer->body->GetLinearVelocity().y;

	EXPECT_GT(velBefore, velAfter);
	EXPECT_GT(velKeyBefore, velKeyAfter);
}

//// SENSORS ////
TEST(SensorButton, OnAction)
{
	b2World * world = new b2World(b2Vec2(0, 9.81));
	TextureManager * texManager = TextureManager::getInstance();
	DoorPlat * door = new DoorPlat(world, sf::Vector2f(-1.5f, 0.f), sf::Vector2f(0.5f, 0.8f), 0.f, true, texManager, "blueGlow");
	MovingPlat *move = new MovingPlat(world, sf::Vector2f(1.5f, 0.f), sf::Vector2f(0.5f, 0.1f), 0.f, sf::Vector2f(1.5f, -1.f), texManager, "yellowPlat", "yellowGlow");
	Button * button = new Button(world, sf::Vector2f(5, 5), sf::Vector2f(1, 1), door, texManager, "yellowLever");
	Button * buttonMove = new Button(world, sf::Vector2f(5, 5), sf::Vector2f(1, 1), move, texManager, "yellowButton");

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
	TextureManager * texManager = TextureManager::getInstance();
	DoorPlat * door = new DoorPlat(world, sf::Vector2f(-1.5f, 0.f), sf::Vector2f(0.5f, 0.8f), 0.f, true, texManager, "blueGlow");
	MovingPlat *move = new MovingPlat(world, sf::Vector2f(1.5f, 0.f), sf::Vector2f(0.5f, 0.1f), 0.f, sf::Vector2f(1.5f, -1.f), texManager, "yellowPlat", "yellowGlow");
	Button * button = new Button(world, sf::Vector2f(5, 5), sf::Vector2f(1, 1), door, texManager, "yellowLever");
	Button * buttonMove = new Button(world, sf::Vector2f(5, 5), sf::Vector2f(1, 1), move, texManager, "yellowButton");

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
	TextureManager * texManager = TextureManager::getInstance();
	PickUp *lightPickUp = new PickUp(world, sf::Vector2f(1.2f, 0.5f), sf::Vector2f(0.1f, 0.1f), 0x0100, texManager);
	Player * player = new Player(world, sf::Vector2f(8.f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0100, texManager);

	bool delBefore = lightPickUp->getDel();
	lightPickUp->onAction(player->body);
	bool delAfter = lightPickUp->getDel();

	EXPECT_NE(delBefore, delAfter);
	EXPECT_EQ(delBefore, false);
	EXPECT_EQ(delAfter, true);
}

//// ANIMATION ////
TEST(Animation, LoopNextFrame)
{
	TextureManager * texMan = TextureManager::getInstance();
	Texture * sprite = new Texture();

	sprite->setLoop(true);
	texMan->setTexture("characters", sprite);
	texMan->getFrames("lightRun", sprite);

	sf::IntRect frameBefore = sprite->frames[sprite->currFrame];
	sprite->nextFrame();
	sf::IntRect frameAfter = sprite->frames[sprite->currFrame];

	EXPECT_NE(frameBefore, frameAfter);
}

TEST(Animation, LoopResetFrame)
{
	TextureManager * texMan = TextureManager::getInstance();
	Texture * sprite = new Texture();

	sprite->setLoop(true);
	texMan->setTexture("characters", sprite);
	texMan->getFrames("lightRun", sprite);
	sprite->currFrame = 3;

	sf::IntRect frameOne = sprite->frames[0];
	sprite->nextFrame();
	sf::IntRect frameAfter = sprite->frames[sprite->currFrame];

	EXPECT_EQ(frameOne, frameAfter);
}

TEST(Animation, NoLoopNextFrame)
{
	TextureManager * texMan = TextureManager::getInstance();
	Texture * sprite = new Texture();

	sprite->setLoop(false);
	texMan->setTexture("characters", sprite);
	texMan->getFrames("lightRun", sprite);

	sf::IntRect frameBefore = sprite->frames[sprite->currFrame];
	sprite->nextFrame();
	sf::IntRect frameAfter = sprite->frames[sprite->currFrame];

	EXPECT_NE(frameBefore, frameAfter);
}

TEST(Animation, NoLoopNoResetFrame)
{
	TextureManager * texMan = TextureManager::getInstance();
	Texture * sprite = new Texture();

	sprite->setLoop(false);
	texMan->setTexture("characters", sprite);
	texMan->getFrames("lightRun", sprite);
	sprite->currFrame = 3;

	sf::IntRect lastFrame = sprite->frames[3];
	sprite->nextFrame();
	sf::IntRect frameAfter = sprite->frames[sprite->currFrame];

	EXPECT_EQ(lastFrame, frameAfter);
}

TEST(Animation, Flip)
{
	TextureManager * texMan = TextureManager::getInstance();
	b2World * world = new b2World(b2Vec2(0, 9.81));
	Player * player = new Player(world, sf::Vector2f(8.f, -2.0f), sf::Vector2f(0.1f, 0.6f), 0.f, 0x0100, texMan);

	player->setAnim();
	texMan->setTexture("characters", player);
	texMan->getFrames("lightRun", player);

	sf::Vector2f scaleBefore = player->currSprite.getScale();
	player->setFlip(true);
	player->update(1.f);
	sf::Vector2f scaleAfter = player->currSprite.getScale();

	EXPECT_NE(scaleBefore.y, scaleAfter.y);
}


//// HUD ////
TEST(HUDUpdate, TimeSeconds)
{
	TextureManager * texMan = TextureManager::getInstance();
	sf::Font font;
	HUD *hud = new HUD(texMan, font);

	auto timeBefore = hud->sec;
	hud->update(1.2f);
	auto timeAfter = hud->sec;

	EXPECT_LT(timeBefore, timeAfter);
}

TEST(HUDUpdate, TimeMinutes)
{
	TextureManager * texMan = TextureManager::getInstance();
	sf::Font font;
	HUD *hud = new HUD(texMan, font);

	hud->sec = 59;

	auto secBefore = hud->sec;
	auto minBefore = hud->min;
	hud->update(1.2f);
	auto secAfter = hud->sec;
	auto minAfter = hud->min;

	EXPECT_GT(secBefore, secAfter);
	EXPECT_EQ(secAfter, 0);
	EXPECT_LT(minBefore, minAfter);
	EXPECT_EQ(minAfter, 1);
}