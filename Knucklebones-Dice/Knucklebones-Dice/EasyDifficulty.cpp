#include "EasyDifficulty.h"


int EasyDifficulty::NextMove(const Board& board, const Board& opponentBoard, int value) const
{
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

	throw std::runtime_error("No empty cells found");
}
