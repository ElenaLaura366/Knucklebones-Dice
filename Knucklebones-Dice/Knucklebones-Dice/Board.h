#pragma once

#include "IGameListener.h"
#include "BasicObservable.h"

#include <vector>
#include <iostream>
#include <map>


class Board : public IObservable
{
public:
	Board();
	Board(Board&&) = default;

	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;
	Board& operator=(Board&&) = delete;

	void MakeMove(int col, int value);
	void CancelValuesInColumn(int col, int value);

	bool IsFull() const;
	bool IsColumnFull(int col) const;

	int CalculateTotalScore() const;

	const std::vector<int>& operator[](int row) const;

	void AddListener(IGameListener* listener) override;
	void RemoveListener(IGameListener* listener) override;
	void NotifyOnBoardUpdate() override;
	void NotifyOnGameOver() override;

private:
	int CalculateColumnScore(int col) const;

private:
	std::vector<std::vector<int>> m_matrix;
	BasicObservable m_observableComponent;
};
