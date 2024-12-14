#pragma once

#include "IGameListener.h"

#include <vector>


namespace game
{
	class IObservable
	{
	public:
		virtual ~IObservable() = default;

		/*!
		*	\brief Adds a listener to the game's list of listeners.
		*	\param listener is the listener to be added to the list.
		*/

		virtual void AddListener(IGameListener* listener) = 0;
		/*!
		*	\brief Removes a listener from the game's list of listeners.
		*	\param listener is the listener to be removed from the list.
		*/

		virtual void RemoveListener(IGameListener* listener) = 0;
		/*!
		*	\brief Notifies all the listeners that the board has been updated.
		*/

		virtual void NotifyOnBoardUpdate() = 0;
		/*!
		*	\brief Notifies all the listeners that the game is over.
		*/

		virtual void NotifyOnGameOver() = 0;
	};
}
