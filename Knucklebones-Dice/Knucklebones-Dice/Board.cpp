#include "Board.h"

#include <unordered_map>


game::Board::Board(int rows, int cols)
	: m_matrix(rows, std::vector<int>(cols, 0))
{
	// empty
}

void game::Board::MakeMove(int col, int value)
{
	CheckColumn(col);
	if (!IsColumnFull(col))
	{
		for (auto& row : m_matrix)
		{
			if (row[col] == 0)
			{
				row[col] = value;
				break;
			}
		}
	}
	else
	{
		throw std::runtime_error("Column is full");
	}
}

void game::Board::CancelValuesInColumn(int col, int value)
{
	CheckColumn(col);
	for (auto& row : m_matrix)
	{
		if (row[col] == value)
		{
			row[col] = 0;
		}
	}
}

bool game::Board::IsFull() const
{
	return std::all_of(m_matrix.begin(), m_matrix.end(), [](const std::vector<int>& row) {
		return std::all_of(row.begin(), row.end(), [](int value) {
			return value != 0;
			});
		});
}

bool game::Board::IsColumnFull(int col) const
{
	CheckColumn(col);
	for (const auto& row : m_matrix)
	{
		if (row[col] == 0)
		{
			return false;
		}
	}
	return true;
}

void game::Board::ChangeCellOnBoard(int row, int col, int value)
{
	if (row < 0 || row >= GetRows() || col < 0 || col >= GetCols())
	{
		throw std::runtime_error("Invalid row or column index");
	}

	m_matrix[row][col] = value;
}

int game::Board::CalculateTotalScore() const
{
	int totalScore = 0;
	for (int col = 0; col < GetCols(); ++col)
	{
		totalScore += CalculateColumnScore(col);
	}
	return totalScore;
}

int game::Board::GetRows() const
{
	return (int)m_matrix.size();
}

int game::Board::GetCols() const
{
	return (int)m_matrix[0].size();
}

const std::vector<int>& game::Board::operator[](int row) const
{
	return m_matrix[row];
}

void game::Board::AddListener(IGameListener* listener)
{
	m_observableComponent.AddListener(listener);
}

void game::Board::RemoveListener(IGameListener* listener)
{
	m_observableComponent.RemoveListener(listener);
}

void game::Board::NotifyOnBoardUpdate()
{
	m_observableComponent.NotifyOnBoardUpdate();
}

void game::Board::NotifyOnGameOver()
{
	m_observableComponent.NotifyOnGameOver();
}

int game::Board::CalculateColumnScore(int col) const
{
	CheckColumn(col);
	std::unordered_map<int, int> valueFrequency;
	for (const auto& row : m_matrix)
	{
		if (row[col] != 0)
		{
			++valueFrequency[row[col]];
		}
	}

	int score = 0;
	for (const auto [value, frequency] : valueFrequency)
	{
		score += value * frequency * frequency;
	}

	return score;
}

void game::Board::CheckColumn(int col) const
{
	if (col < 0 || col >= GetCols())
	{
		throw std::runtime_error("Invalid column index");
	}
}
