#include "HardDifficulty.h"


int game::HardDifficulty::NextMove(const Board& board, const Board& opponentBoard, int value) const
{
	for (int row = 0; row < opponentBoard.GetRows(); ++row)
	{
		for (int col = 0; col < opponentBoard.GetCols(); ++col)
		{
			if (opponentBoard[row][col] == value)
			{
				for (int myRow = 0; myRow < board.GetRows(); ++myRow)
				{
					if (board[myRow][col] == 0)
					{
						return col;
					}
				}
			}
		}
	}

	for (int row = 0; row < board.GetRows(); ++row)
	{
		for (int col = 0; col < board.GetCols(); ++col)
		{
			if (board[row][col] == 0)
			{
				return col;
			}
		}
	}
}
