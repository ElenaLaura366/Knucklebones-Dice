#include "HardDifficulty.h"


int game::HardDifficulty::NextMove(const Board& board, const Board& opponentBoard, int value) const
{
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			if (opponentBoard[row][col] == value)
			{
				return col;
			}
		}
	}

	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			if (board[row][col] == 0)
			{
				return col;
			}
		}
	}
}
