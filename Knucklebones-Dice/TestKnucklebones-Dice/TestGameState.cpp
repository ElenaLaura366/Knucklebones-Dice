#include "GameState.h"
#include "Player.h"

#include <gtest/gtest.h>


class GameStateTest : public ::testing::Test
{
protected:
	Player player1;
	Player player2;
	GameState gameState;

public:
	GameStateTest()
		: player1("Alice")
		, player2("Bob")
		, gameState(player1, player2)
	{
		// empty
	}

	virtual void SetUp()
	{
		// empty
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
