#pragma once

#include "IOpponentDifficulty.h"


namespace game
{
	//! Class representing an easy difficulty opponent.
	class EasyDifficulty : public IOpponentDifficulty
	{
	public:
		EasyDifficulty() = default;

		//! Easy difficulty opponent move.
		/*!
		*   The easy difficulty opponent will make a move where it finds the first empty cell.
		*   \param board is the board of the current player, that represents the computer.
		*	\param opponentBoard is the board of the opposing player.
		*	\param value is the value the player rolled.
		*/
		int NextMove(const Board& board, const Board& opponentBoard, int value) const override;
	};
}
