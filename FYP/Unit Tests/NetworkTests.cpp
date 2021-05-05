#include "NetworkTests.h"

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
	PlayerUpdate update;
	update.player = 1;
	update.texture = 2;
	update.frame = 3;
	update.flip = false;
	update.dead = false;
	update.position = sf::Vector2f(0.5f, 1.2f);
	p << update;

	state.HandlePackets(7, p, nullptr);

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
	PlayerUpdate update;
	update.player = 2;
	update.texture = 2;
	update.frame = 3;
	update.flip = false;
	update.dead = false;
	update.position = sf::Vector2f(0.5f, 1.2f);
	p << update;

	state.HandlePackets(7, p, nullptr);

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
	LevelUpdate update;
	update.object = 3;
	update.index = 0;
	update.texture = true;
	update.frame = 2;
	p << update;

	state.HandlePackets(8, p, nullptr);

	Level * lvl = game->game->currLevel;

	bool texture = lvl->levers[0]->getTexture();
	int frame = lvl->levers[0]->getFrame();

	EXPECT_EQ(texture, update.texture);
	EXPECT_EQ(frame, update.frame);
}

TEST(ClientPacketRecieved, MovingPlatformLevelUpdate)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	int score = 1;
	GameState * game = new GameState(0, &score, &netStates);
	netStates.push(game);
	state.currState = netStates.top();

	sf::Packet p;
	LevelUpdate update;
	update.object = 0;
	update.index = 0;
	update.position = sf::Vector2f(2.4f, 4.6f);
	update.texture = false;
	p << update;

	state.HandlePackets(8, p, nullptr);

	Level * lvl = game->game->currLevel;

	sf::Vector2f pos = lvl->movingPlats[0]->currSprite.getPosition();
	bool texture = lvl->movingPlats[0]->glowTex;

	EXPECT_EQ(pos.x, update.position.x);
	EXPECT_EQ(pos.y, update.position.y);
	EXPECT_EQ(texture, update.texture);
}

TEST(ClientPacketRecieved, DoorPlatformLevelUpdate)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	int score = 1;
	GameState * game = new GameState(1, &score, &netStates);
	netStates.push(game);
	state.currState = netStates.top();

	sf::Packet p;
	LevelUpdate update;
	update.object = 1;
	update.index = 0;
	update.position = sf::Vector2f(2.4f, 4.6f);
	p << update;

	state.HandlePackets(8, p, nullptr);

	Level * lvl = game->game->currLevel;

	sf::Vector2f pos = lvl->doorPlats[0]->platform->currSprite.getPosition();

	EXPECT_EQ(pos.x, update.position.x);
	EXPECT_EQ(pos.y, update.position.y);
}

TEST(ClientPacketRecieved, TiltPlatformLevelUpdate)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	int score = 1;
	GameState * game = new GameState(1, &score, &netStates);
	netStates.push(game);
	state.currState = netStates.top();

	sf::Packet p;
	LevelUpdate update;
	update.object = 2;
	update.index = 0;
	update.angle = 0.2f;
	p << update;

	state.HandlePackets(8, p, nullptr);

	Level * lvl = game->game->currLevel;

	float angle = lvl->tiltPlats[0]->currSprite.getRotation();
	angle /= 57.29577f;

	EXPECT_EQ(angle, update.angle);
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
	LevelUpdate update;
	update.object = 4;
	update.index = 0;
	update.position = sf::Vector2f(5.8f, 3.7f);
	update.angle = 0.964f;
	p << update;

	state.HandlePackets(8, p, nullptr);

	Level * lvl = game->game->currLevel;

	sf::Vector2f pos = lvl->blocks[0]->currSprite.getPosition();
	float angle = lvl->blocks[0]->currSprite.getRotation();

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
	LevelUpdate update;
	update.object = 5;
	update.index = 2;
	p << update;

	state.HandlePackets(8, p, nullptr);

	Level * lvl = game->game->currLevel;

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
	LevelUpdate update;
	update.object = 6;
	update.index = 1;
	p << update;

	state.HandlePackets(8, p, nullptr);

	Level * lvl = game->game->currLevel;

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
	LevelUpdate update;
	update.object = 7;
	update.texture = true;
	p << update;

	state.HandlePackets(8, p, nullptr);

	Level * lvl = game->game->currLevel;

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
	LevelUpdate update;
	update.object = 8;
	update.texture = true;
	p << update;

	state.HandlePackets(8, p, nullptr);

	Level * lvl = game->game->currLevel;

	bool fade = lvl->darkHome->getFade();

	EXPECT_EQ(fade, update.texture);
}

TEST(ClientPacketRecieved, GameOverMove)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	int score = 1;
	GameState * game = new GameState(0, &score, &netStates);
	netStates.push(game);
	state.currState = netStates.top();
	game->game->over = true;

	int backBefore = game->game->getText();

	sf::Packet p;
	LevelSelectUpdate update;
	update.currLevel = 1;
	p << update;

	state.HandlePackets(5, p, nullptr);

	int back = game->game->getText();

	EXPECT_EQ(backBefore, 0);
	EXPECT_EQ(back, update.currLevel);
}

TEST(ClientPacketRecieved, GameOverRetry)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	int score = 1;
	GameState * game = new GameState(0, &score, &netStates);
	netStates.push(game);
	state.currState = netStates.top();
	game->game->over = true;

	sf::Packet p;
	bool up = true;
	p << up;

	state.HandlePackets(6, p, nullptr);

	bool retry = game->game->getRetry();

	EXPECT_EQ(retry, true);

	Game * oldGame = game->game;
	game->update(1.f);
	Game * newGame = game->game;

	EXPECT_NE(oldGame, newGame);
}

TEST(ClientPacketRecieved, GameOverReturn)
{
	NetworkState state;
	std::stack<State *> netStates = state.netStates;
	int score = 1;
	GameState * game = new GameState(0, &score, &netStates);
	netStates.push(game);
	state.currState = netStates.top();
	game->game->over = true;

	sf::Packet p;
	bool up = false;
	p << up;

	state.HandlePackets(6, p, nullptr);

	bool back = game->game->levelSelect;

	EXPECT_EQ(back, true);

	game->update(1.f);

	EXPECT_EQ(game->quit, true);
}


//// SERVER ////
//// Client 0 Level Select Controls ////
TEST(Client0ToServer, LevelSelectDown)
{
	LevelSelectState state(1024, 800, nullptr, nullptr);

	int lvlBefore = state.levelSelect->getLevel();

	sf::Packet p;
	p << sf::Keyboard::Key::Down;

	mockHandler(3, p, 0, &state);

	//state.processNetworkKeyPress(74, nullptr, 0);	// Down key, null server, client 0
	// Get packet somehow?
	int lvl = state.levelSelect->getLevel();
	
	EXPECT_EQ(lvl, 1);
	EXPECT_EQ(lvlBefore, 0);
}

TEST(Client0ToServer, LevelSelectUp)
{
	LevelSelectState state(1024, 800, nullptr, nullptr);

	state.levelSelect->selectedLevel = 1;

	int lvlBefore = state.levelSelect->getLevel();

	sf::Packet p;
	p << sf::Keyboard::Key::Up;

	mockHandler(3, p, 0, &state);

	int lvl = state.levelSelect->getLevel();

	EXPECT_EQ(lvl, 0);
	EXPECT_EQ(lvlBefore, 1);
}

TEST(Client0ToServer, LevelSelectRight)
{
	LevelSelectState state(1024, 800, nullptr, nullptr);

	int backBefore = state.levelSelect->getBack();

	sf::Packet p;
	p << sf::Keyboard::Key::Right;

	mockHandler(3, p, 0, &state);

	int back = state.levelSelect->getBack();

	EXPECT_EQ(back, 1);
	EXPECT_EQ(backBefore, 0);
}

TEST(Client0ToServer, LevelSelectLeft)
{
	LevelSelectState state(1024, 800, nullptr, nullptr);

	state.levelSelect->back = 1;

	int backBefore = state.levelSelect->getBack();

	sf::Packet p;
	p << sf::Keyboard::Key::Left;

	mockHandler(3, p, 0, &state);

	int back = state.levelSelect->getBack();

	EXPECT_EQ(back, 0);
	EXPECT_EQ(backBefore, 1);
}

TEST(Client0ToServer, EnterLevel)
{
	std::stack<State *> states;
	LevelSelectState * lvlSelect = new LevelSelectState(1024, 800, &states);
	states.push(lvlSelect);

	bool playBefore = lvlSelect->levelSelect->getPlay();

	sf::Packet p;
	p << sf::Keyboard::Key::Return;

	mockHandler(3, p, 0, lvlSelect);

	bool play = lvlSelect->levelSelect->getPlay();
	lvlSelect->update(1.f);

	EXPECT_EQ(playBefore, false);
	EXPECT_EQ(play, true);
	EXPECT_NE(states.top(), lvlSelect);
	EXPECT_EQ(states.size(), 2);
}

TEST(Client0ToServer, EnterMenu)
{
	std::stack<State *> states;
	LevelSelectState * lvlSelect = new LevelSelectState(1024, 800, &states);
	states.push(lvlSelect);
	lvlSelect->levelSelect->back = 1;

	bool backBefore = lvlSelect->levelSelect->getClose();

	sf::Packet p;
	p << sf::Keyboard::Key::Return;

	mockHandler(3, p, 0, lvlSelect);

	bool back = lvlSelect->levelSelect->getClose();
	lvlSelect->update(1.f);

	EXPECT_EQ(backBefore, false);
	EXPECT_EQ(back, true);
	EXPECT_EQ(lvlSelect->getQuit(), true);
}


//// Client 1 Level Select Controls ////
TEST(Client1ToServer, LevelSelectDown)
{
	LevelSelectState state(1024, 800, nullptr, nullptr);

	int lvlBefore = state.levelSelect->getLevel();

	sf::Packet p;
	p << sf::Keyboard::Key::Down;

	mockHandler(3, p, 1, &state);

	int lvl = state.levelSelect->getLevel();

	EXPECT_EQ(lvl, 1);
	EXPECT_EQ(lvlBefore, 0);
}

TEST(Client1ToServer, LevelSelectUp)
{
	LevelSelectState state(1024, 800, nullptr, nullptr);

	state.levelSelect->selectedLevel = 1;

	int lvlBefore = state.levelSelect->getLevel();

	sf::Packet p;
	p << sf::Keyboard::Key::Up;

	mockHandler(3, p, 1, &state);

	int lvl = state.levelSelect->getLevel();

	EXPECT_EQ(lvl, 0);
	EXPECT_EQ(lvlBefore, 1);
}

TEST(Client1ToServer, LevelSelectRight)
{
	LevelSelectState state(1024, 800, nullptr, nullptr);

	int backBefore = state.levelSelect->getBack();

	sf::Packet p;
	p << sf::Keyboard::Key::Right;

	mockHandler(3, p, 1, &state);

	int back = state.levelSelect->getBack();

	EXPECT_EQ(back, 1);
	EXPECT_EQ(backBefore, 0);
}

TEST(Client1ToServer, LevelSelectLeft)
{
	LevelSelectState state(1024, 800, nullptr, nullptr);

	state.levelSelect->back = 1;

	int backBefore = state.levelSelect->getBack();

	sf::Packet p;
	p << sf::Keyboard::Key::Left;

	mockHandler(3, p, 1, &state);

	int back = state.levelSelect->getBack();

	EXPECT_EQ(back, 0);
	EXPECT_EQ(backBefore, 1);
}

TEST(Client1ToServer, EnterLevel)
{
	std::stack<State *> states;
	LevelSelectState * lvlSelect = new LevelSelectState(1024, 800, &states);
	states.push(lvlSelect);

	bool playBefore = lvlSelect->levelSelect->getPlay();

	sf::Packet p;
	p << sf::Keyboard::Key::Return;

	mockHandler(3, p, 1, lvlSelect);

	bool play = lvlSelect->levelSelect->getPlay();
	lvlSelect->update(1.f);

	EXPECT_EQ(playBefore, false);
	EXPECT_EQ(play, true);
	EXPECT_NE(states.top(), lvlSelect);
	EXPECT_EQ(states.size(), 2);
}

TEST(Client1ToServer, EnterMenu)
{
	std::stack<State *> states;
	LevelSelectState * lvlSelect = new LevelSelectState(1024, 800, &states);
	states.push(lvlSelect);
	lvlSelect->levelSelect->back = 1;

	bool backBefore = lvlSelect->levelSelect->getClose();

	sf::Packet p;
	p << sf::Keyboard::Key::Return;

	mockHandler(3, p, 1, lvlSelect);

	bool back = lvlSelect->levelSelect->getClose();
	lvlSelect->update(1.f);

	EXPECT_EQ(backBefore, false);
	EXPECT_EQ(back, true);
	EXPECT_EQ(lvlSelect->getQuit(), true);
}

//// Client 1 Game Controls ////
TEST(Client1ToServer, GameLeft)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);

	bool darkBefore = state.game->darkLeft;

	sf::Packet p;
	p << sf::Keyboard::Key::Left;

	mockHandler(3, p, 1, &state);

	bool dark = state.game->darkLeft;

	EXPECT_EQ(darkBefore, false);
	EXPECT_EQ(dark, true);
}

TEST(Client1ToServer, GameRight)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);

	bool darkBefore = state.game->darkRight;

	sf::Packet p;
	p << sf::Keyboard::Key::Right;

	mockHandler(3, p, 1, &state);

	bool dark = state.game->darkRight;

	EXPECT_EQ(darkBefore, false);
	EXPECT_EQ(dark, true);
}

TEST(Client1ToServer, GameUp)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);

	for (int i = 0; i < 5; i++) state.game->update(1.f, true);
	b2Vec2 darkBefore = state.game->currLevel->darkPlayer->body->GetLinearVelocity();

	sf::Packet p;
	p << sf::Keyboard::Key::Up;

	mockHandler(3, p, 1, &state);

	b2Vec2 dark = state.game->currLevel->darkPlayer->body->GetLinearVelocity();

	EXPECT_EQ(darkBefore.x, dark.x);
	EXPECT_GT(darkBefore.y, dark.y);
}

TEST(Client1ToServer, GameKeyA)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);

	bool lightBefore = state.game->lightLeft;

	sf::Packet p;
	p << sf::Keyboard::Key::A;

	mockHandler(3, p, 1, &state);

	bool light = state.game->lightLeft;

	EXPECT_EQ(lightBefore, light);
}

TEST(Client1ToServer, GameKeyD)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);

	bool lightBefore = state.game->lightRight;

	sf::Packet p;
	p << sf::Keyboard::Key::D;

	mockHandler(3, p, 1, &state);

	bool light = state.game->lightRight;

	EXPECT_EQ(lightBefore, light);
}

TEST(Client1ToServer, GameKeyW)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);

	for (int i = 0; i < 5; i++) state.game->update(1.f, true);
	b2Vec2 lightBefore = state.game->currLevel->lightPlayer->body->GetLinearVelocity();

	sf::Packet p;
	p << sf::Keyboard::Key::W;

	mockHandler(3, p, 1, &state);

	b2Vec2 light = state.game->currLevel->lightPlayer->body->GetLinearVelocity();

	EXPECT_EQ(lightBefore.x, light.x);
	EXPECT_EQ(lightBefore.y, light.y);
}

//// Client 0 Game Controls ////
TEST(Client0ToServer, GameLeft)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);

	bool darkBefore = state.game->darkLeft;

	sf::Packet p;
	p << sf::Keyboard::Key::Left;

	mockHandler(3, p, 0, &state);

	bool dark = state.game->darkLeft;

	EXPECT_EQ(darkBefore, dark);
}

TEST(Client0ToServer, GameRight)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);

	bool darkBefore = state.game->darkRight;

	sf::Packet p;
	p << sf::Keyboard::Key::Right;

	mockHandler(3, p, 0, &state);

	bool dark = state.game->darkRight;

	EXPECT_EQ(darkBefore, dark);
}

TEST(Client0ToServer, GameUp)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);

	for (int i = 0; i < 5; i++) state.game->update(1.f, true);
	b2Vec2 darkBefore = state.game->currLevel->darkPlayer->body->GetLinearVelocity();

	sf::Packet p;
	p << sf::Keyboard::Key::Up;

	mockHandler(3, p, 0, &state);

	b2Vec2 dark = state.game->currLevel->darkPlayer->body->GetLinearVelocity();

	EXPECT_EQ(darkBefore.x, dark.x);
	EXPECT_EQ(darkBefore.y, dark.y);
}

TEST(Client0ToServer, GameKeyA)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);

	bool lightBefore = state.game->lightLeft;

	sf::Packet p;
	p << sf::Keyboard::Key::A;

	mockHandler(3, p, 0, &state);

	bool light = state.game->lightLeft;

	EXPECT_EQ(lightBefore, false);
	EXPECT_EQ(light, true);
}

TEST(Client0ToServer, GameKeyD)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);

	bool lightBefore = state.game->lightRight;

	sf::Packet p;
	p << sf::Keyboard::Key::D;

	mockHandler(3, p, 0, &state);

	bool light = state.game->lightRight;

	EXPECT_EQ(lightBefore, false);
	EXPECT_EQ(light, true);
}

TEST(Client0ToServer, GameKeyW)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);

	for (int i = 0; i < 5; i++) state.game->update(1.f, true);
	b2Vec2 lightBefore = state.game->currLevel->lightPlayer->body->GetLinearVelocity();

	sf::Packet p;
	p << sf::Keyboard::Key::W;

	mockHandler(3, p, 0, &state);

	b2Vec2 light = state.game->currLevel->lightPlayer->body->GetLinearVelocity();

	EXPECT_EQ(lightBefore.x, light.x);
	EXPECT_GT(lightBefore.y, light.y);
}

//// GAME OVER ////
TEST(Client1ToServer, GameOverLeft)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);
	state.game->over = true;
	state.game->back = 1;

	int backBefore = state.game->back;

	sf::Packet p;
	p << sf::Keyboard::Key::Left;

	mockHandler(3, p, 1, &state);

	int back = state.game->back;

	EXPECT_EQ(backBefore, 1);
	EXPECT_EQ(back, 0);
}

TEST(Client1ToServer, GameOverRight)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);
	state.game->over = true;

	int backBefore = state.game->back;

	sf::Packet p;
	p << sf::Keyboard::Key::Right;

	mockHandler(3, p, 1, &state);

	int back = state.game->back;

	EXPECT_EQ(backBefore, 0);
	EXPECT_EQ(back, 1);
}

TEST(Client1ToServer, GameOverRetry)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);
	state.game->over = true;

	sf::Packet p;
	p << sf::Keyboard::Key::Return;

	mockHandler(3, p, 1, &state);

	bool retry = state.game->retry;

	EXPECT_EQ(retry, true);
}

TEST(Client1ToServer, GameOverReturn)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);
	state.game->over = true;

	state.game->back = 1;

	sf::Packet p;
	p << sf::Keyboard::Key::Return;

	mockHandler(3, p, 1, &state);

	bool back = state.game->levelSelect;

	EXPECT_EQ(back, true);
}

TEST(Client0ToServer, GameOverLeft)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);
	state.game->over = true;
	state.game->back = 1;

	int backBefore = state.game->back;

	sf::Packet p;
	p << sf::Keyboard::Key::Left;

	mockHandler(3, p, 0, &state);

	int back = state.game->back;

	EXPECT_EQ(backBefore, 1);
	EXPECT_EQ(back, 0);
}

TEST(Client0ToServer, GameOverRight)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);
	state.game->over = true;

	int backBefore = state.game->back;

	sf::Packet p;
	p << sf::Keyboard::Key::Right;

	mockHandler(3, p, 0, &state);

	int back = state.game->back;

	EXPECT_EQ(backBefore, 0);
	EXPECT_EQ(back, 1);
}

TEST(Client0ToServer, GameOverRetry)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);
	state.game->over = true;

	sf::Packet p;
	p << sf::Keyboard::Key::Return;

	mockHandler(3, p, 0, &state);

	bool retry = state.game->retry;

	EXPECT_EQ(retry, true);
}

TEST(Client0ToServer, GameOverReturn)
{
	std::stack<State *> netStates;
	int score = 1;
	GameState state(0, &score, &netStates, nullptr);
	state.game->over = true;

	state.game->back = 1;

	sf::Packet p;
	p << sf::Keyboard::Key::Return;

	mockHandler(3, p, 0, &state);

	bool back = state.game->levelSelect;

	EXPECT_EQ(back, true);
}