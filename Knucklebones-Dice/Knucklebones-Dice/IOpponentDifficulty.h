#pragma once

#include "Board.h"


namespace game
{
	class IOpponentDifficulty
	{
	public:
		virtual ~IOpponentDifficulty() = default;
		//! Method to get the next move of the opponent based on the difficulty.
		virtual int NextMove(const Board& board, const Board& opponentBoard, int value) const = 0;
	};
}
