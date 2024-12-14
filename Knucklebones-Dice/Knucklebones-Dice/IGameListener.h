#pragma once

#include <memory>


namespace game
{
	class IGameListener
	{
	public:
		virtual ~IGameListener() = default;
		//! Action to be taken when the game notifies that the board has been updated.
		virtual void OnBoardUpdate() = 0;
		//! Action to be taken when the game notifies that the game is over.
		virtual void OnGameOver() = 0;
	};
}
