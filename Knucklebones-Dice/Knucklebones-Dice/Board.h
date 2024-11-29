#pragma once
#include "IGameListener.h"
#include "Observable.h"
#include <vector>
#include <memory>
#include <iostream>

class Board : public Observable
{
public:
    Board();

    void MakeMove(int col, int value);
    bool IsColumnFull(int col) const;
    bool IsFull() const;

    const std::vector<std::vector<int>>& GetBoard() const;

private:
    std::vector<std::vector<int>> m_board;

    void NotifyMove(); // Notifică observatorii despre o schimbare pe tablă
};