#pragma once
#include <gtest/gtest.h>

#define private public
#define protected public
#include "NetworkState.h"
//#include "ServerMock.h"

/*
	HOW TO
	- Add client
	- Client DC

	- Check corrosponding function called for packet

	- Wait, will I have to mock the other functions for this....
		- Check info passed up the function chain
			- Functions called in sequence
		- Check what packet is returned
			- Check correct info in packet
				- Exact values if known
				- Structure type if not?
	
*/

TEST(ClientPacketRecieved, UpdateLevelSelectLevel)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	LevelSelectState * lvlSelect = new LevelSelectState(1024, 800, &netStates);
	netStates.push(lvlSelect);
	state.currState = netStates.top();

	sf::Packet p;
	LevelSelectUpdate update;
	update.currLevel = 3;
	update.back = 0;
	p << update;

	state.HandlePackets(5, p, nullptr);
	
	int level = lvlSelect->levelSelect->getLevel();
	int back = lvlSelect->levelSelect->getBack();

	EXPECT_EQ(level, update.currLevel);
	EXPECT_EQ(back, update.back);
}

TEST(ClientPacketRecieved, UpdateLevelSelectBack)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	LevelSelectState * lvlSelect = new LevelSelectState(1024, 800, &netStates);
	netStates.push(lvlSelect);
	state.currState = netStates.top();

	sf::Packet p;
	LevelSelectUpdate update;
	update.currLevel = 0;
	update.back = 1;
	p << update;

	state.HandlePackets(5, p, nullptr);

	int level = lvlSelect->levelSelect->getLevel();
	int back = lvlSelect->levelSelect->getBack();

	EXPECT_EQ(level, update.currLevel);
	EXPECT_EQ(back, update.back);
}

TEST(ClientPacketRecieved, PushStateFromLevelSelect)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	LevelSelectState * lvlSelect = new LevelSelectState(1024, 800, &netStates);
	netStates.push(lvlSelect);
	state.currState = netStates.top();

	sf::Packet p;
	bool up = true;
	p << up;

	state.HandlePackets(6, p, nullptr);

	bool play = lvlSelect->levelSelect->getPlay();

	EXPECT_EQ(play, true);

	lvlSelect->update(1.f);
	state.currState = netStates.top();

	EXPECT_NE(state.currState, lvlSelect);
	EXPECT_EQ(netStates.size(), 2);
}

TEST(ClientPacketRecieved, PopStateFromLevelSelect)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	LevelSelectState * lvlSelect = new LevelSelectState(1024, 800, &netStates);
	netStates.push(lvlSelect);
	state.currState = netStates.top();

	sf::Packet p;
	bool up = false;
	p << up;

	state.HandlePackets(6, p, nullptr);

	bool exit = lvlSelect->levelSelect->getClose();

	EXPECT_EQ(exit, true);

	lvlSelect->update(1.f);

	EXPECT_EQ(state.currState->getQuit(), true);
}

TEST(ClientPacketRecieved, LightPlayerUpdate)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	int score = 1;
	GameState * game = new GameState(0, &score, &netStates);
	netStates.push(game);
	state.currState = netStates.top();

	sf::Packet p;
	StampPacket(PacketType::PlayerUpdate, p);
	PlayerUpdate update;
	update.player = 1;
	update.texture = 2;
	update.frame = 3;
	update.flip = false;
	update.dead = false;
	update.position = sf::Vector2f(0.5f, 1.2f);
	p << update;

	state.HandlePackets(7, p, nullptr);
	// Compare values before and after handle packet
	// Check they are equal to values sent in packet

	int texture = game->game->currLevel->lightPlayer->getLightTex();
	int fram = game->game->currLevel->lightPlayer->getFrame();
	bool flip = game->game->currLevel->lightPlayer->getFlip();
	bool dead = game->game->currLevel->lightPlayer->getDead();
	sf::Vector2f pos = game->game->currLevel->lightPlayer->currSprite.getPosition();

	EXPECT_EQ(texture, update.texture);
	EXPECT_EQ(fram, update.frame);
	EXPECT_EQ(flip, update.flip);
	EXPECT_EQ(dead, update.dead);
	EXPECT_EQ(pos.x, update.position.x);
	EXPECT_EQ(pos.y, update.position.y);
}

TEST(ClientPacketRecieved, DarkPlayerUpdate)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	int score = 1;
	GameState * game = new GameState(0, &score, &netStates);
	netStates.push(game);
	state.currState = netStates.top();

	sf::Packet p;
	StampPacket(PacketType::PlayerUpdate, p);
	PlayerUpdate update;
	update.player = 2;
	update.texture = 2;
	update.frame = 3;
	update.flip = false;
	update.dead = false;
	update.position = sf::Vector2f(0.5f, 1.2f);
	p << update;

	state.HandlePackets(7, p, nullptr);
	// Compare values before and after handle packet
	// Check they are equal to values sent in packet

	int texture = game->game->currLevel->darkPlayer->getDarkTex();
	int fram = game->game->currLevel->darkPlayer->getFrame();
	bool flip = game->game->currLevel->darkPlayer->getFlip();
	bool dead = game->game->currLevel->darkPlayer->getDead();
	sf::Vector2f pos = game->game->currLevel->darkPlayer->currSprite.getPosition();

	EXPECT_EQ(texture, update.texture);
	EXPECT_EQ(fram, update.frame);
	EXPECT_EQ(flip, update.flip);
	EXPECT_EQ(dead, update.dead);
	EXPECT_EQ(pos.x, update.position.x);
	EXPECT_EQ(pos.y, update.position.y);
}

TEST(ClientPacketRecieved, LeverLevelUpdate)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	int score = 1;
	GameState * game = new GameState(0, &score, &netStates);
	netStates.push(game);
	state.currState = netStates.top();

	sf::Packet p;
	StampPacket(PacketType::LevelUpdate, p);
	LevelUpdate update;
	update.object = 0;
	update.texture = true;
	update.frame = 2;
	p << update;

	state.HandlePackets(8, p, nullptr);

	Lvl1 * lvl = (Lvl1*)game->game->currLevel;

	int texture = lvl->lever->getTexture();
	int frame = lvl->lever->getFrame();

	EXPECT_EQ(texture, update.texture);
	EXPECT_EQ(frame, update.frame);
}

TEST(ClientPacketRecieved, PlatformLevelUpdate)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	int score = 1;
	GameState * game = new GameState(0, &score, &netStates);
	netStates.push(game);
	state.currState = netStates.top();

	sf::Packet p;
	StampPacket(PacketType::LevelUpdate, p);
	LevelUpdate update;
	update.object = 1;
	update.index = 0;
	update.position = sf::Vector2f(2.4f, 4.6f);
	update.texture = false;
	p << update;

	state.HandlePackets(8, p, nullptr);

	Lvl1 * lvl = (Lvl1*)game->game->currLevel;

	sf::Vector2f pos = lvl->platforms[0]->currSprite.getPosition();
	bool texture = lvl->platforms[0]->glowTex;

	EXPECT_EQ(pos.x, update.position.x);
	EXPECT_EQ(pos.y, update.position.y);
	EXPECT_EQ(texture, update.texture);
}

TEST(ClientPacketRecieved, BlockLevelUpdate)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	int score = 1;
	GameState * game = new GameState(0, &score, &netStates);
	netStates.push(game);
	state.currState = netStates.top();

	sf::Packet p;
	StampPacket(PacketType::LevelUpdate, p);
	LevelUpdate update;
	update.object = 2;
	update.position = sf::Vector2f(5.8f, 3.7f);
	update.angle = 0.964f;
	p << update;

	state.HandlePackets(8, p, nullptr);

	Lvl1 * lvl = (Lvl1*)game->game->currLevel;

	sf::Vector2f pos = lvl->block->currSprite.getPosition();
	float angle = lvl->block->currSprite.getRotation();
	
	EXPECT_EQ(pos.x, update.position.x);
	EXPECT_EQ(pos.y, update.position.y);
	EXPECT_EQ(angle, update.angle * 57.29577f);
}

TEST(ClientPacketRecieved, LightItemLevelUpdate)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	int score = 1;
	GameState * game = new GameState(0, &score, &netStates);
	netStates.push(game);
	state.currState = netStates.top();

	sf::Packet p;
	StampPacket(PacketType::LevelUpdate, p);
	LevelUpdate update;
	update.object = 3;
	update.index = 2;
	p << update;

	state.HandlePackets(8, p, nullptr);

	Lvl1 * lvl = (Lvl1*)game->game->currLevel;

	bool del = lvl->lightPickUps[2]->getDel();

	EXPECT_EQ(del, true);
}

TEST(ClientPacketRecieved, DarkItemLevelUpdate)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	int score = 1;
	GameState * game = new GameState(0, &score, &netStates);
	netStates.push(game);
	state.currState = netStates.top();

	sf::Packet p;
	StampPacket(PacketType::LevelUpdate, p);
	LevelUpdate update;
	update.object = 4;
	update.index = 1;
	p << update;

	state.HandlePackets(8, p, nullptr);

	Lvl1 * lvl = (Lvl1*)game->game->currLevel;

	bool del = lvl->darkPickUps[1]->getDel();

	EXPECT_EQ(del, true);
}

TEST(ClientPacketRecieved, LightHomeLevelUpdate)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	int score = 1;
	GameState * game = new GameState(0, &score, &netStates);
	netStates.push(game);
	state.currState = netStates.top();

	sf::Packet p;
	StampPacket(PacketType::LevelUpdate, p);
	LevelUpdate update;
	update.object = 5;
	update.texture = true;
	p << update;

	state.HandlePackets(8, p, nullptr);

	Lvl1 * lvl = (Lvl1*)game->game->currLevel;

	bool fade = lvl->lightHome->getFade();

	EXPECT_EQ(fade, update.texture);
}

TEST(ClientPacketRecieved, DarkHomeLevelUpdate)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	int score = 1;
	GameState * game = new GameState(0, &score, &netStates);
	netStates.push(game);
	state.currState = netStates.top();

	sf::Packet p;
	StampPacket(PacketType::LevelUpdate, p);
	LevelUpdate update;
	update.object = 6;
	update.texture = true;
	p << update;

	state.HandlePackets(8, p, nullptr);

	Lvl1 * lvl = (Lvl1*)game->game->currLevel;

	bool fade = lvl->darkHome->getFade();

	EXPECT_EQ(fade, update.texture);
}