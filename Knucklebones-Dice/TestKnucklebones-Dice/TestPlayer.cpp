#include <gtest/gtest.h>
#include "Player.h"
#include "Board.h"

class PlayerTest : public ::testing::Test {
protected:
    Player player;
    Board board;

    virtual void SetUp() {
        player.setPlayer("Alice");
        player.setBoard(board);
    }
};

// Test player name setting and retrieval
TEST_F(PlayerTest, PlayerSettings) {
    EXPECT_EQ(player.getPlayer(), "Alice");
    Player newPlayer("Bob", board);
    EXPECT_EQ(newPlayer.getPlayer(), "Bob");
}

// Test board settings
TEST_F(PlayerTest, BoardSettings) {
    Board newBoard;
    player.setBoard(newBoard);
    // Assuming we can compare Boards or have a method to validate this
    EXPECT_EQ(player.getBoard(), newBoard);
}

// Test initial score settings
TEST_F(PlayerTest, InitialScore) {
    EXPECT_EQ(player.getScore(), 0);
}

// Test score updates and reset
TEST_F(PlayerTest, ScoreUpdateAndReset) {
    player.updateScore(20);
    EXPECT_EQ(player.getScore(), 20);

    player.updateScore(30);
    EXPECT_EQ(player.getScore(), 50);

    player.resetScore();
    EXPECT_EQ(player.getScore(), 0);
}

// Test setting an exact score
TEST_F(PlayerTest, SetExactScore) {
    player.setScore(100);
    EXPECT_EQ(player.getScore(), 100);
}

