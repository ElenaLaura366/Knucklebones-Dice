#pragma once

#include "IGameListener.h"
#include "BasicObservable.h"

#include <vector>
#include <iostream>


namespace game
{
	class Board : public IObservable
	{
	public:
		Board(int rows = Board::DefaultRows, int cols = Board::DefaultCols);
		Board(Board&&) = default;

		Board(const Board&) = delete;
		Board& operator=(const Board&) = delete;
		Board& operator=(Board&&) = delete;

		void MakeMove(int col, int value);
		void CancelValuesInColumn(int col, int value);
		int CalculateTotalScore() const;

		bool IsFull() const;
		bool IsColumnFull(int col) const;

		int GetRows() const;
		int GetCols() const;
		const std::vector<int>& operator[](int row) const;

		void AddListener(IGameListener* listener) override;
		void RemoveListener(IGameListener* listener) override;
		void NotifyOnBoardUpdate() override;
		void NotifyOnGameOver() override;

	private:
		int CalculateColumnScore(int col) const;
		void CheckColumn(int col) const;

	public:
		static constexpr int DefaultRows = 3;
		static constexpr int DefaultCols = 3;

	private:
		std::vector<std::vector<int>> m_matrix;
		BasicObservable m_observableComponent;
	};
}
