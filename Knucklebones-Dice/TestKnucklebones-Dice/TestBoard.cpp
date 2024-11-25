#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Board.h"

class BoardTest : public ::testing::Test {
protected:
    Board board;

    virtual void SetUp() {
        board.setPlayer("TestPlayer");
    }
};

// Test initialization of the board
TEST_F(BoardTest, InitialState) {
    EXPECT_EQ(board.getPlayer(), "TestPlayer");
    for (int col = 0; col < 3; ++col) {
        EXPECT_FALSE(board.isColumnFull(col));
    }
}

// Test the move making in various columns
TEST_F(BoardTest, MakeMove) {
    board.makeMove(0, 1);
    EXPECT_EQ(board.getBoard(0, 0)[0][0], 1);
    board.makeMove(1, 2);
    EXPECT_EQ(board.getBoard(0, 0)[0][1], 2);
    board.makeMove(2, 1);
    EXPECT_EQ(board.getBoard(0, 0)[0][2], 1);
}

// Test column full check after multiple moves
TEST_F(BoardTest, ColumnFullCheck) {
    board.makeMove(0, 1);
    board.makeMove(0, 2);
    board.makeMove(0, 1);
    EXPECT_TRUE(board.isColumnFull(0));
    EXPECT_FALSE(board.isColumnFull(1));
    EXPECT_FALSE(board.isColumnFull(2));
}

// Test the score calculation
TEST_F(BoardTest, CalculateScore) {
    board.makeMove(0, 1);
    board.makeMove(0, 2);
    board.makeMove(0, 1);
    board.makeMove(1, 1);
    board.makeMove(1, 1);
    board.makeMove(1, 1);
    board.makeMove(2, 2);
    board.makeMove(2, 2);
    board.makeMove(2, 2);
    int expectedScore = 1 * 1 * 1 + 2 * 2 * 2 + 1 * 1 * 1 + // column 0
        1 * 1 * 1 + 1 * 1 * 1 + 1 * 1 * 1 + // column 1
        2 * 2 * 2 + 2 * 2 * 2 + 2 * 2 * 2;  // column 2
    EXPECT_EQ(board.boardScore(), expectedScore);
}

// Test board display functionality
TEST_F(BoardTest, DisplayBoard) {
    testing::internal::CaptureStdout();
    board.makeMove(0, 1);
    board.displayBoard();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_THAT(output, testing::HasSubstr("1 . . \n. . . \n. . . \n"));
}
