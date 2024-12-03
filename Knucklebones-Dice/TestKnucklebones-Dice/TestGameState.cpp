#include "GameState.h"
#include "Player.h"

#include <gtest/gtest.h>


class GameStateTest : public ::testing::Test
{
protected:
	GameState gameState;
	Player player1{ "Alice" };
	Player player2{ "Bob" };

	virtual void SetUp()
	{
		gameState.AddPlayer(player1);
		gameState.AddPlayer(player2);
	}
};

TEST_F(GameStateTest, ActivePlayerRotation)
{
	EXPECT_EQ(gameState.GetActivePlayer().GetName(), "Alice");

	gameState.NextPlayer();
	EXPECT_EQ(gameState.GetActivePlayer().GetName(), "Bob");

	gameState.NextPlayer();
	EXPECT_EQ(gameState.GetActivePlayer().GetName(), "Alice");
}

TEST_F(GameStateTest, CheckGameOver)
{
	for (int col = 0; col < 3; ++col)
	{
		for (int i = 0; i < 3; ++i)
		{
			gameState.GetActiveBoard().MakeMove(col, 1);
		}
	}
	gameState.CheckForGameOver();
	EXPECT_FALSE(gameState.IsGameActive());
}

TEST_F(GameStateTest, UpdateScores)
{
	gameState.GetActiveBoard().MakeMove(0, 1);
	gameState.GetActiveBoard().MakeMove(0, 1);
	gameState.UpdateScores();
	EXPECT_EQ(player1.GetScore(), 4);
}
