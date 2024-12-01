#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "IGameListener.h"

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