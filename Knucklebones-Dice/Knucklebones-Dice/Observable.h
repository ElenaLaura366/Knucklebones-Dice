#pragma once

#include "IGameListener.h"

#include <vector>
#include <memory>
#include <algorithm>


class Observable
{
public:
	void AddListener(IGameListener* observer);
	void RemoveListener(IGameListener* observer);

protected:
	void NotifyOnBoardUpdate();
	void NotifyOnGameOver();

private:
	std::vector<IGameListener*> m_observers;
};
