#include <gtest/gtest.h>
#include "ScoreTracker.h"
#include "Player.h"
#include "Board.h"

class ScoreTrackerTest : public ::testing::Test {
protected:
    ScoreTracker scoreTracker;
    Board board;
    std::vector<Player> players;

    virtual void SetUp() {
        players.emplace_back("Alice", board);
        players.emplace_back("Bob", board);
    }
};

// Test updating a player's score based on the board state
TEST_F(ScoreTrackerTest, UpdatePlayerScore) {
    board.makeMove(0, 1);
    board.makeMove(0, 2);
    board.makeMove(0, 1);
    scoreTracker.updateScore(players[0]);
    EXPECT_GT(players[0].getScore(), 0);  // Expect score to be greater than 0
}

// Test evaluating score from a board setup
TEST_F(ScoreTrackerTest, EvaluateScore) {
    board.makeMove(0, 1);
    board.makeMove(1, 2);
    board.makeMove(2, 1);
    auto scoreData = scoreTracker.evaluateScore(board);
    EXPECT_GT(scoreData.first, 0);  // Score should be calculated and greater than 0
    EXPECT_GE(scoreData.second, 1);  // Multiplier should at least be 1
}

// Test finding the winner index from a list of players
TEST_F(ScoreTrackerTest, GetWinnerIndex) {
    players[0].setScore(50);
    players[1].setScore(70);
    int winnerIndex = scoreTracker.getWinnerIndex(players);
    EXPECT_EQ(winnerIndex, 1);  // Bob should be the winner
}

// Test displaying scores using only Google Test functionalities
TEST_F(ScoreTrackerTest, DisplayScores) {
    players[0].setScore(30);
    players[1].setScore(40);
    testing::internal::CaptureStdout();  // Start capturing stdout
    scoreTracker.displayScores(players);
    std::string output = testing::internal::GetCapturedStdout();  // Get the captured output
    EXPECT_NE(output.find("Alice: 30"), std::string::npos);
    EXPECT_NE(output.find("Bob: 40"), std::string::npos);
}
