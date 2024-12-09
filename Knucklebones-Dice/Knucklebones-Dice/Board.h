#pragma once

#include "IGameListener.h"
#include "Observable.h"

#include <vector>
#include <iostream>
#include <map>


class Board : public Observable
{
public:
	Board();
	Board(Board&&) = default;

	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;
	Board& operator=(Board&&) = delete;

	void MakeMove(int col, int value);
	bool IsColumnFull(int col) const;
	bool IsFull() const;

	const std::vector<std::vector<int>>& GetBoard() const;
	void CancelValuesInColumn(int col, int value);

	int CalculateTotalScore() const;
	int CalculateColumnScore(int col) const;

	const std::vector<int>& operator[](int row) const;
	std::vector<int>& operator[](int row);

private:
	std::vector<std::vector<int>> m_board;

	void NotifyMove();
};
