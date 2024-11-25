#include <gtest/gtest.h>
#include "GameState.h"
#include "Player.h"
#include "Board.h"

class GameStateTest : public ::testing::Test {
protected:
    GameState gameState;

    virtual void SetUp() {
        Player alice("Alice", Board());
        gameState.addPlayer(alice);
        Player bob("Bob", Board());
        gameState.addPlayer(bob);
        Player carol("Carol", Board());
        gameState.addPlayer(carol);
    }
};

// Test the addition of players and active player functionality
TEST_F(GameStateTest, ActivePlayer) {
    EXPECT_EQ(gameState.getActivePlayer().getPlayer(), "Alice");

    gameState.nextPlayer();
    EXPECT_EQ(gameState.getActivePlayer().getPlayer(), "Bob");

    gameState.nextPlayer();
    EXPECT_EQ(gameState.getActivePlayer().getPlayer(), "Carol");
}

// Test game over by score
TEST_F(GameStateTest, GameOverByScore) {
    gameState.getActivePlayer().setScore(60); // Alice scores 60
    EXPECT_FALSE(gameState.checkGameOver(50));

    gameState.nextPlayer();
    gameState.getActivePlayer().setScore(70); // Bob scores 70
    EXPECT_TRUE(gameState.checkGameOver(50)); // Bob wins, game over should be true
}

// Test ending the game manually
TEST_F(GameStateTest, EndGame) {
    gameState.endGame();
    EXPECT_FALSE(gameState.isGameActive());
}

// Test the winner determination
TEST_F(GameStateTest, DetermineWinner) {
    gameState.getActivePlayer().setScore(30); // Alice scores 30

    gameState.nextPlayer();
    gameState.getActivePlayer().setScore(70); // Bob scores 70

    gameState.nextPlayer();
    gameState.getActivePlayer().setScore(50); // Carol scores 50

    EXPECT_EQ(gameState.getWinner().getPlayer(), "Bob");
    EXPECT_EQ(gameState.getWinner().getScore(), 70);
}

