#pragma once
#include <gtest/gtest.h>

#define private public
#define protected public
#include "MenuState.h"

TEST(PushStates, StateMenu)
{
	std::stack<State *> states;

	State *expected = new MenuState(1024, 800, &states);

	states.push(expected);

	State *firstState = states.top();

	EXPECT_EQ(firstState, expected);
}

TEST(PushStates, StateLevelSelect)
{
	std::stack<State *> states;

	State *expected = new LevelSelectState(1024, 800, &states);

	states.push(expected);

	State *firstState = states.top();

	EXPECT_EQ(firstState, expected);
}

TEST(PushStates, StateGame)
{
	std::stack<State *> states;
	int score = 1;
	State *expected = new GameState(0, &score, &states);

	states.push(expected);

	State *firstState = states.top();

	EXPECT_EQ(firstState, expected);
}


TEST(States, NewState)
{
	std::stack<State *> states;

	State *first = new MenuState(1024, 800, &states);
	states.push(first);
	State *firstState = states.top();

	State *second = new LevelSelectState(1024, 800, &states);
	states.push(second);
	State *secondState = states.top();

	EXPECT_EQ(first, firstState);
	EXPECT_EQ(second, secondState);
	EXPECT_NE(firstState, secondState);
}

TEST(States, DeleteState)
{
	std::stack<State *> states;

	State *first = new MenuState(1024, 800, &states);
	states.push(first);
	State *firstState = states.top();
	State *currState = states.top();

	EXPECT_EQ(first, currState);
	EXPECT_EQ(first, firstState);

	State *second = new LevelSelectState(1024, 800, &states);
	states.push(second);
	State *secondState = states.top();
	currState = states.top();

	EXPECT_EQ(second, currState);
	EXPECT_EQ(second, secondState);
	EXPECT_NE(firstState, secondState);

	delete states.top();
	states.pop();

	if (!states.empty())
		currState = states.top();

	EXPECT_EQ(currState, firstState);
}