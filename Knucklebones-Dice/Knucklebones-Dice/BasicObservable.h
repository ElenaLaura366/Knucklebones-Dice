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
		void AddListener(IGameListener* listener) override;
		void RemoveListener(IGameListener* listener) override;
		void NotifyOnBoardUpdate() override;
		void NotifyOnGameOver() override;

	private:
		std::vector<IGameListener*> m_observers;
	};
}
