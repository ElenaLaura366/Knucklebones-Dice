#include "Observable.h"

#include "IGameListener.h"


void Observable::AddListener(IGameListener* observer)
{
	m_observers.push_back(observer);
}

void Observable::RemoveListener(IGameListener* observer)
{
	m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
}

void Observable::NotifyOnBoardUpdate()
{
	for (auto observer : m_observers)
	{
		observer->OnBoardUpdate();
	}
}

void Observable::NotifyOnGameOver()
{
	for (auto observer : m_observers)
	{
		observer->OnGameOver();
	}
}
