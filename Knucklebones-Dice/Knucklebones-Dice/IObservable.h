#pragma once

#include "IGameListener.h"

#include <vector>


namespace game
{
	class IObservable
	{
	public:
		virtual ~IObservable() = default;
		virtual void AddListener(IGameListener* observer) = 0;
		virtual void RemoveListener(IGameListener* observer) = 0;
		virtual void NotifyOnBoardUpdate() = 0;
		virtual void NotifyOnGameOver() = 0;
	};
}
