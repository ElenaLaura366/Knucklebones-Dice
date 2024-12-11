#pragma once

#include "IOpponentDifficulty.h"


class HardDifficulty : public IOpponentDifficulty
{
public:
	HardDifficulty() = default;
	int NextMove(const Board& board, const Board& opponentBoard, int value) const override;
};
