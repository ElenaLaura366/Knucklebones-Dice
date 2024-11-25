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

std::vector<std::vector<int>> Board::getBoard(int row, int col) const
{
    return this->m_board;
}

bool Board::isColumnFull(int col) 
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

void Board::makeMove(int col, int value) {
    if (!isColumnFull(col)) 
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
}

int Board::boardScore() {
    int score = 0;
    for (int col = 0; col < 3; ++col) {
        std::unordered_map<int, int> count;
        for (int row = 0; row < 3; ++row) {
            if (m_board[row][col] > 0) {
                count[m_board[row][col]]++;
            }
        }
        for (auto it = count.begin(); it != count.end(); ++it) {
            int value = it->first;
            int freq = it->second;
            score += value * freq * freq;
        }

    }
    return score;
}

void Board::displayBoard() const 
{
    for (const auto& row : m_board) 
    {
        for (const auto& cell : row) 
        {
            std::cout << (cell == 0 ? "." : std::to_string(cell)) << " ";
        }
        std::cout << "\n";
    }
}
