#include "EasyDifficulty.h"


int game::EasyDifficulty::NextMove(const Board& board, const Board& opponentBoard, int value) const
{
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

	throw std::runtime_error("No empty cells found");
}
