#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "IGameListener.h"

class Game
{
public:
    void MakeMove(int col, int value);

    int GetMoves() const;
    void EndGame();

    void AddListener(IGameListenerPtr listener);
    void RemoveListener(IGameListener* listener);

private:
    int m_moves = 0;
    bool m_gameActive = true;
    std::vector<IGameListenerWeakPtr> m_listeners;

    void NotifyOnBoardUpdate();
    void NotifyOnGameOver();
};