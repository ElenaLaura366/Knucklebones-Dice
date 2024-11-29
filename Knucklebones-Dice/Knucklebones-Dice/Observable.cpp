#include "Observable.h"
#include "IGameListener.h"

void Observable::AddListener(const std::shared_ptr<IGameListener>& observer)
{
    m_observers.push_back(observer);
}

void Observable::RemoveListener(IGameListener* observer)
{
    for (auto it = m_observers.begin(); it != m_observers.end(); )
    {
        if (auto sp = it->lock()) {
            if (sp.get() == observer) {
                it = m_observers.erase(it);
            }
            else {
                ++it;
            }
        }
        else {
            it = m_observers.erase(it);
        }
    }
}

void Observable::NotifyOnBoardUpdate()
{
    for (auto& weakPtr : m_observers) {
        if (auto sp = weakPtr.lock()) {
            sp->OnBoardUpdate();
        }
    }
}

void Observable::NotifyOnGameOver()
{
    for (auto& weakPtr : m_observers) {
        if (auto sp = weakPtr.lock()) {
            sp->OnGameOver();
        }
    }
}
