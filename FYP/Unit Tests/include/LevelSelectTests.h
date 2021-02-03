#pragma once
#include <gtest/gtest.h>

#define private public
#define protected public
#include "..\FYP\include\Menu\LevelSelect.h"

TEST(Navigation, MoveUpAtTop)
{
	LevelSelect select(1024, 800);

	int initial = select.selectedLevel;
	sf::Keyboard::Key key = sf::Keyboard::Up;
	select.processKeyPress(key);
	int after = select.selectedLevel;

	EXPECT_EQ(initial, after);
	EXPECT_EQ(initial, 0);
	EXPECT_EQ(after, 0);
}

TEST(Navigation, MoveUp)
{
	LevelSelect select(1024, 800);

	select.selectedLevel = 1;
	int initial = select.selectedLevel;
	sf::Keyboard::Key key = sf::Keyboard::Up;
	select.processKeyPress(key);
	int after = select.selectedLevel;

	EXPECT_EQ(initial, 1);
	EXPECT_EQ(after, 0);
	EXPECT_NE(initial, after);
}

TEST(Navigation, MoveDownAtBottom)
{
	LevelSelect select(1024, 800);

	select.selectedLevel = 5;
	int initial = select.selectedLevel;
	sf::Keyboard::Key key = sf::Keyboard::Down;
	select.processKeyPress(key);
	int after = select.selectedLevel;

	EXPECT_EQ(initial, after);
	EXPECT_EQ(initial, 5);
	EXPECT_EQ(after, 5);
}

TEST(Navigation, MoveDown)
{
	LevelSelect select(1024, 800);

	int initial = select.selectedLevel;
	sf::Keyboard::Key key = sf::Keyboard::Down;
	select.processKeyPress(key);
	int after = select.selectedLevel;

	EXPECT_EQ(initial, 0);
	EXPECT_EQ(after, 1);
	EXPECT_NE(initial, after);
}

TEST(Navigation, MoveRightAtRight)
{
	LevelSelect select(1024, 800);

	select.back = 1;
	int initial = select.back;
	sf::Keyboard::Key key = sf::Keyboard::Right;
	select.processKeyPress(key);
	int after = select.back;

	EXPECT_EQ(initial, after);
	EXPECT_EQ(initial, 1);
	EXPECT_EQ(after, 1);
}

TEST(Navigation, MoveRight)
{
	LevelSelect select(1024, 800);

	int initial = select.back;
	sf::Keyboard::Key key = sf::Keyboard::Right;
	select.processKeyPress(key);
	int after = select.back;

	EXPECT_EQ(initial, 0);
	EXPECT_EQ(after, 1);
	EXPECT_NE(initial, after);
}

TEST(Navigation, MoveLeftAtLeft)
{
	LevelSelect select(1024, 800);

	int initial = select.back;
	sf::Keyboard::Key key = sf::Keyboard::Left;
	select.processKeyPress(key);
	int after = select.back;

	EXPECT_EQ(initial, after);
	EXPECT_EQ(initial, 0);
	EXPECT_EQ(after, 0);
}

TEST(Navigation, MoveLeft)
{
	LevelSelect select(1024, 800);

	select.back = 1;
	int initial = select.back;
	sf::Keyboard::Key key = sf::Keyboard::Left;
	select.processKeyPress(key);
	int after = select.back;

	EXPECT_EQ(initial, 1);
	EXPECT_EQ(after, 0);
	EXPECT_NE(initial, after);
}

TEST(Navigation, MoveUpDownAtMenu)
{
	LevelSelect select(1024, 800);

	select.back = 1;
	select.selectedLevel = 3;


	int downInitial = select.selectedLevel;
	sf::Keyboard::Key key = sf::Keyboard::Down;
	select.processKeyPress(key);
	int downAfter = select.selectedLevel;

	EXPECT_EQ(downInitial, downAfter);
	EXPECT_EQ(downInitial, 3);
	EXPECT_EQ(downAfter, 3);


	int upInitial = select.selectedLevel;
	key = sf::Keyboard::Up;
	select.processKeyPress(key);
	int upAfter = select.selectedLevel;

	EXPECT_EQ(upInitial, upAfter);
	EXPECT_EQ(upInitial, 3);
	EXPECT_EQ(upAfter, 3);
}

TEST(Navigation, SelectMenu)
{
	LevelSelect select(1024, 800);

	select.back = 1;

	bool closeBefore = select.getClose();
	sf::Keyboard::Key key = sf::Keyboard::Return;
	select.processKeyPress(key);
	bool closeAfter = select.getClose();

	EXPECT_EQ(closeBefore, false);
	EXPECT_EQ(closeAfter, true);
	EXPECT_NE(closeBefore, closeAfter);
}

TEST(Navigation, SelectLevel)
{
	LevelSelect select(1024, 800);

	bool playBefore = select.getPlay();
	sf::Keyboard::Key key = sf::Keyboard::Return;
	select.processKeyPress(key);
	bool playAfter = select.getPlay();

	EXPECT_EQ(playBefore, false);
	EXPECT_EQ(playAfter, true);
	EXPECT_NE(playBefore, playAfter);
}


TEST(LevelTextures, LevelPreview)
{
	LevelSelect select(1024, 800);

	auto first = select.preview.spriteSheet;
	auto firstExpected = select.texManager->getTexture("onePreview");
	sf::Keyboard::Key key = sf::Keyboard::Down;
	select.processKeyPress(key);
	select.update(1.f);
	auto second = select.preview.spriteSheet;
	auto secondExpected = select.texManager->getTexture("twoPreview");

	EXPECT_EQ(first, firstExpected);
	EXPECT_EQ(second, secondExpected);
	EXPECT_NE(first, second);
}

TEST(LevelTextures, StarScore)
{
	LevelSelect select(1024, 800);

	auto inital = select.texManager->getState();
	select.score[4] = 1;
	select.update(1.f);
	auto red = select.texManager->getState();
	select.score[4] = 2;
	select.update(1.f);
	auto orange = select.texManager->getState();
	select.score[4] = 3;
	select.update(1.f);
	auto green = select.texManager->getState();

	EXPECT_EQ(inital, "Empty");
	EXPECT_EQ(red, "Red");
	EXPECT_EQ(orange, "Orange");
	EXPECT_EQ(green, "Green");
}