#include "Board.h"
#include "EasyDifficulty.h"
#include "HardDifficulty.h"

#include <gtest/gtest.h>

namespace test
{
    class HardDifficultyTest : public ::testing::Test
    {
    protected:
        game::HardDifficulty hard;

        game::Board CreateBoard(const std::vector<std::vector<int>>& values)
        {
            game::Board board;
            for (int row = 0; row < 3; ++row)
            {
                for (int col = 0; col < 3; ++col)
                {
                    board.ChangeCellOnBoard(row, col, values[row][col]);
                }
            }
            return board;
        }
    };

    TEST_F(HardDifficultyTest, StealsValueFromOpponentBoard)
    {
        game::Board playerBoard = CreateBoard({ {0, 0, 0}, {0, 0, 0}, {0, 0, 0} });

        game::Board opponentBoard = CreateBoard({ {0, 5, 0}, {0, 0, 0}, {0, 0, 0} });

        int nextMove = hard.NextMove(playerBoard, opponentBoard, 5);

        EXPECT_EQ(nextMove, 1);

        EXPECT_EQ(opponentBoard[0][1], 0);
    }

    TEST_F(HardDifficultyTest, StealsValueCorrectlyWhenMultipleOptions)
    {
        game::Board playerBoard = CreateBoard({ {0, 0, 0}, {0, 0, 0}, {0, 0, 0} });
        game::Board opponentBoard = CreateBoard({ {0, 5, 0}, {3, 0, 0}, {0, 0, 0} });

        int nextMove = hard.NextMove(playerBoard, opponentBoard, 3);

        EXPECT_EQ(nextMove, 0);

        EXPECT_EQ(opponentBoard[1][0], 0);
    }

    TEST_F(HardDifficultyTest, PicksEmptyCellWhenNoValueToSteal)
    {
        game::Board playerBoard = CreateBoard({ {1, 2, 3}, {4, 5, 6}, {0, 0, 0} });
        game::Board opponentBoard = CreateBoard({ {1, 2, 3}, {4, 5, 6}, {1, 2, 3} });

        int nextMove = hard.NextMove(playerBoard, opponentBoard, 1);

        EXPECT_EQ(nextMove, 0);
    }
}
