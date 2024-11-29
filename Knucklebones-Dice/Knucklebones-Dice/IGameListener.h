#pragma once
#include <memory>

class IGameListener
{
public:
    virtual void OnBoardUpdate() = 0;
    virtual void OnGameOver() = 0;

    virtual ~IGameListener() = default;
};

using IGameListenerPtr = std::shared_ptr<IGameListener>;
using IGameListenerWeakPtr = std::weak_ptr<IGameListener>;