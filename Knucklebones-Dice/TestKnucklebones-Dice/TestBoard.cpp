#include "Board.h"

#include <gtest/gtest.h>


namespace test
{
	class BoardTest : public ::testing::Test
	{
	protected:
		game::Board board;
	};

	TEST_F(BoardTest, InitialState)
	{
		for (int col = 0; col < 3; ++col)
		{
			EXPECT_FALSE(board.IsColumnFull(col));
		}
		EXPECT_FALSE(board.IsFull());
	}

	TEST_F(BoardTest, MakeMove)
	{
		board.MakeMove(0, 1);
		EXPECT_EQ(board[0][0], 1);

		board.MakeMove(1, 2);
		EXPECT_EQ(board[0][1], 2);

		board.MakeMove(2, 3);
		EXPECT_EQ(board[0][2], 3);
	}

	TEST_F(BoardTest, ColumnFullCheck)
	{
		board.MakeMove(0, 1);
		board.MakeMove(0, 2);
		board.MakeMove(0, 3);
		EXPECT_TRUE(board.IsColumnFull(0));
		EXPECT_FALSE(board.IsColumnFull(1));
	}

	TEST_F(BoardTest, CalculateScore)
	{
		board.MakeMove(0, 1);
		board.MakeMove(0, 1);
		board.MakeMove(0, 1);

		EXPECT_EQ(std::as_const(board).CalculateTotalScore(), 9);
	}

	TEST_F(BoardTest, CancelValuesInColumn)
	{
		board.MakeMove(0, 2);
		board.MakeMove(0, 2);
		board.CancelValuesInColumn(0, 2);

		EXPECT_EQ(board[0][0], 0);
		EXPECT_EQ(board[1][0], 0);
	}
}
