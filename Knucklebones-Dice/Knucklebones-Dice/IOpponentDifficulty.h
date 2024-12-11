#pragma once

#include "Board.h"


class IOpponentDifficulty
{
public:
	virtual ~IOpponentDifficulty() = default;
	virtual int NextMove(const Board& board, const Board& opponentBoard, int value) const = 0;
};
