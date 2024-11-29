#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "IGameListener.h"

class Observable
{
public:
    void AddListener(const std::shared_ptr<IGameListener>& observer);
    void RemoveListener(IGameListener* observer);

protected:
    void NotifyOnBoardUpdate();
    void NotifyOnGameOver();

private:
    std::vector<std::weak_ptr<IGameListener>> m_observers;
};