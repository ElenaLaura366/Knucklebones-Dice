#pragma once

#include "IOpponentDifficulty.h"


namespace game
{
	//! Class representing an hard difficulty opponent.
	class HardDifficulty : public IOpponentDifficulty
	{
	public:
		HardDifficulty() = default;

		//! Hard difficulty opponent move.
		/*!
		*   The hard difficulty opponent will make a move where it can steal a value from the opponent board, if not it finds the first empty cell.
		*   \param board is the board of the current player, that represents the computer.
		*	\param opponentBoard is the board of the opposing player.
		*	\param value is the value the player rolled.
		*/
		int NextMove(const Board& board, const Board& opponentBoard, int value) const override;
	};
}
