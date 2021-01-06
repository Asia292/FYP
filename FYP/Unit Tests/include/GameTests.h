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