#include "Game.h"
#include "Player.h"

#include <gtest/gtest.h>


class GameTest : public ::testing::Test
{
protected:
	Game game{ "Alice", "Bob", nullptr };
};

TEST_F(GameTest, ActivePlayerRotation)
{
	EXPECT_EQ(std::as_const(game).GetActivePlayer().GetName(), "Alice");

	game.MakeMove(0, 1);
	EXPECT_EQ(std::as_const(game).GetActivePlayer().GetName(), "Bob");

	game.MakeMove(0, 1);
	EXPECT_EQ(std::as_const(game).GetActivePlayer().GetName(), "Alice");
}

TEST_F(GameTest, CheckGameOver)
{
	for (int col = 0; col < 3; ++col)
	{
		for (int row = 0; row < 3; ++row)
		{
			game.MakeMove(col, 1);
			game.MakeMove(col, 2);
		}
	}
	EXPECT_TRUE(game.IsGameOver());
}

TEST_F(GameTest, CheckScores)
{
	game.MakeMove(0, 1);
	game.MakeMove(0, 2);

	EXPECT_EQ(game.CalculateScore(1), 1);
	EXPECT_EQ(game.CalculateScore(2), 2);

	game.MakeMove(0, 1);
	game.MakeMove(0, 2);
	EXPECT_EQ(game.CalculateScore(1), 4);
	EXPECT_EQ(game.CalculateScore(2), 8);

	game.MakeMove(0, 1);
	game.MakeMove(0, 2);

	EXPECT_EQ(game.CalculateScore(1), 9);
	EXPECT_EQ(game.CalculateScore(2), 18);
}
