#include "Board.h"


Board::Board()
	: m_matrix(3, std::vector<int>(3, 0))
{
	// empty
}

void Board::MakeMove(int col, int value)
{
	if (!IsColumnFull(col))
	{
		for (int row = 0; row < 3; ++row)
		{
			if (m_matrix[row][col] == 0)
			{
				m_matrix[row][col] = value;
				break;
			}
		}
	}
}

void Board::CancelValuesInColumn(int col, int value)
{
	for (int row = 0; row < 3; ++row)
	{
		if (m_matrix[row][col] == value)
		{
			m_matrix[row][col] = 0;
		}
	}
}

bool Board::IsFull() const
{
	return std::all_of(m_matrix.begin(), m_matrix.end(), [](const std::vector<int>& row) {
		return std::all_of(row.begin(), row.end(), [](int value) {
			return value != 0;
			});
		});
}

bool Board::IsColumnFull(int col) const
{
	for (int row = 0; row < 3; ++row)
	{
		if (m_matrix[row][col] == 0)
		{
			return false;
		}
	}
	return true;
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

const std::vector<int>& Board::operator[](int row) const
{
	return m_matrix[row];
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

int Board::CalculateColumnScore(int col) const
{
	std::map<int, int> valueFrequency;
	for (int row = 0; row < 3; ++row)
	{
		if (m_matrix[row][col] != 0)
		{
			valueFrequency[m_matrix[row][col]]++;
		}
	}

	int score = 0;
	for (const auto& [value, frequency] : valueFrequency)
	{
		score += value * frequency * frequency;
	}

	return score;
}
