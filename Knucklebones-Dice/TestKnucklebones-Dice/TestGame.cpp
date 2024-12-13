#include "Game.h"
#include "Player.h"

#include <gtest/gtest.h>


class GameTest : public ::testing::Test, public IGameListener
{
public:
	GameTest()
		: game("Alice", "Bob", nullptr)
	{
		game.AddListener(this);
	}

	void OnGameOver() override
	{
		++gameOverCallCount;
	}

	void OnBoardUpdate() override
	{
		// empty
	}

protected:
	Game game;
	int gameOverCallCount = 0;
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
	for (int col = 0; col < std::as_const(game).GetActiveBoard().GetCols(); ++col)
	{
		for (int row = 0; row < std::as_const(game).GetActiveBoard().GetRows(); ++row)
		{
			game.MakeMove(col, 1);
			game.MakeMove(col, 2);
		}
	}
	EXPECT_EQ(gameOverCallCount, 2);
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
