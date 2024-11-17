#include "Board.h"

Board::Board() : m_board(3, std::vector<int>(3, 0))
{
}

Board::~Board()
{
}

void Board::Update()
{
}

void Board::setPlayer(std::string name)
{
	this->m_player = name;
}

std::string Board::getPlayer()
{
	return m_player;
}

std::vector<std::vector<int>> Board::getBoard(int row, int col)
{
	return this->m_board;
}

void Board::makeMove(int col, int value)
{
	for (int i = 0; i < 3; i++)
	{
		if (m_board[i][col] == 0)
		{
			m_board[i][col] = value;
			break;
		}
	}
}

int Board::boardScore()
{
	return 0;//TODO
}
