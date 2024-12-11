#include "BasicObservable.h"

#include "IGameListener.h"


void BasicObservable::AddListener(IGameListener* listener)
{
	m_observers.push_back(listener);
}

void BasicObservable::RemoveListener(IGameListener* listener)
{
	m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), listener), m_observers.end());
}

void BasicObservable::NotifyOnBoardUpdate()
{
	for (IGameListener* observer : m_observers)
	{
		observer->OnBoardUpdate();
	}
}

void BasicObservable::NotifyOnGameOver()
{
	for (IGameListener* observer : m_observers)
	{
		observer->OnGameOver();
	}
}
