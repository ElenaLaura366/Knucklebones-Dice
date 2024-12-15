#pragma once

#include "IOpponentDifficulty.h"


namespace game
{
	class HardDifficulty : public IOpponentDifficulty
	{
	public:
		HardDifficulty() = default;
		int NextMove(const Board& board, const Board& opponentBoard, int value) const override;
		void ClearCellOnOpponentBoard(Board& opponentBoard, int value) const;
	};
}
