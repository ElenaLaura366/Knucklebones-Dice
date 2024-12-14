#pragma once

#include "IOpponentDifficulty.h"


namespace game
{
	class EasyDifficulty : public IOpponentDifficulty
	{
	public:
		EasyDifficulty() = default;
		int NextMove(const Board& board, const Board& opponentBoard, int value) const override;
	};
}
