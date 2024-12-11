#include "Game.h"
#include "Player.h"

#include <gtest/gtest.h>


class GameTest : public ::testing::Test
{
protected:
	Game game;

public:
	GameTest()
		: game("Alice", "Bob")
	{
		// empty
	}

	virtual void SetUp()
	{
		// empty
	}
};

TEST_F(GameTest, ActivePlayerRotation)
{
	EXPECT_EQ(game.GetActivePlayer().GetName(), "Alice");

	game.NextPlayer();
	EXPECT_EQ(game.GetActivePlayer().GetName(), "Bob");

	game.NextPlayer();
	EXPECT_EQ(game.GetActivePlayer().GetName(), "Alice");
}

TEST_F(GameTest, CheckGameOver)
{
	for (int col = 0; col < 3; ++col)
	{
		for (int i = 0; i < 3; ++i)
		{
			game.GetActiveBoard().MakeMove(col, 1);
		}
	}
	EXPECT_FALSE(game.IsGameActive());
}

TEST_F(GameTest, UpdateScores)
{
	game.GetActiveBoard().MakeMove(0, 1);
	game.GetActiveBoard().MakeMove(0, 1);
	game.UpdateScores();
	EXPECT_EQ(game.GetPlayer1().GetScore(), 4);
}
