#pragma once

#include "IObservable.h"

#include <vector>
#include <memory>
#include <algorithm>


namespace game
{
	class BasicObservable : public IObservable
	{
	public:
		/*!
		*	Adds a listener to the game's list of listeners.
		*	\param listener is the listener to be added to the list.
		*/
		void AddListener(IGameListener* listener) override;
		/*!
		*	Removes a listener from the game's list of listeners.
		*	\param listener is the listener to be removed from the list.
		*/
		void RemoveListener(IGameListener* listener) override;
		/*!
		*	Notifies all the listeners that the board has been updated.
		*/
		void NotifyOnBoardUpdate() override;
		/*!
		*	Notifies all the listeners that the game is over.
		*/
		void NotifyOnGameOver() override;

	private:
		std::vector<IGameListener*> m_observers;
	};
}
