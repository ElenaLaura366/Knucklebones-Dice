#include "Board.h"


Board::Board()
	: m_board(3, std::vector<int>(3, 0))
{
	// empty
}

void Board::MakeMove(int col, int value)
{
	if (!IsColumnFull(col))
	{
		for (int row = 0; row < 3; ++row)
		{
			if (m_board[row][col] == 0)
			{
				m_board[row][col] = value;
				break;
			}
		}
	}
}

int Board::CalculateTotalScore() const
{
	int totalScore = 0;
	for (int col = 0; col < 3; ++col)
	{
		totalScore += CalculateColumnScore(col);
	}
	return totalScore;
}

int Board::CalculateColumnScore(int col) const
{
	std::map<int, int> valueFrequency;
	for (int row = 0; row < 3; ++row)
	{
		if (m_board[row][col] != 0)
		{
			valueFrequency[m_board[row][col]]++;
		}
	}

	int score = 0;
	for (const auto& [value, frequency] : valueFrequency)
	{
		score += value * frequency * frequency;
	}

	return score;
}

bool Board::IsColumnFull(int col) const
{
	for (int row = 0; row < 3; ++row)
	{
		if (m_board[row][col] == 0)
		{
			return false;
		}
	}
	return true;
}

bool Board::IsFull() const
{
	return std::all_of(m_board.begin(), m_board.end(), [](const std::vector<int>& row) {
		return std::all_of(row.begin(), row.end(), [](int value) {
			return value != 0;
			});
		});
}

const std::vector<std::vector<int>>& Board::GetBoard() const
{
	return m_board;
}

void Board::NotifyMove()
{
	NotifyOnBoardUpdate();
}

void Board::CancelValuesInColumn(int col, int value)
{
	for (int row = 0; row < 3; ++row)
	{
		if (m_board[row][col] == value)
		{
			m_board[row][col] = 0;
		}
	}
}

const std::vector<int>& Board::operator[](int row) const
{
	return m_board[row];
}

std::vector<int>& Board::operator[](int row)
{
	return m_board[row];
}

void Board::AddListener(IGameListener* listener)
{
	m_observableComponent.AddListener(listener);
}

void Board::RemoveListener(IGameListener* listener)
{
	m_observableComponent.RemoveListener(listener);
}

void Board::NotifyOnBoardUpdate()
{
	m_observableComponent.NotifyOnBoardUpdate();
}

void Board::NotifyOnGameOver()
{
	m_observableComponent.NotifyOnGameOver();
}
