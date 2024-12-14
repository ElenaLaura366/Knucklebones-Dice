#include "BasicObservable.h"

#include "IGameListener.h"


void game::BasicObservable::AddListener(IGameListener* listener)
{
	m_observers.push_back(listener);
}

void game::BasicObservable::RemoveListener(IGameListener* listener)
{
	m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), listener), m_observers.end());
}

void game::BasicObservable::NotifyOnBoardUpdate()
{
	for (IGameListener* observer : m_observers)
	{
		observer->OnBoardUpdate();
	}
}

void game::BasicObservable::NotifyOnGameOver()
{
	for (IGameListener* observer : m_observers)
	{
		observer->OnGameOver();
	}
}
