#include "Board.h"


Board::Board() : m_board(3, std::vector<int>(3, 0)), m_opponentBoard(3, std::vector<int>(3, 0)) {}

void Board::MakeMove(int col, int value)
{
    if (!IsColumnFull(col))
    {
        RemoveOpponentDice(col, value);

        for (int row = 0; row < 3; ++row)
        {
            if (m_board[row][col] == 0)
            {
                m_board[row][col] = value;
                NotifyMove();
                break;
            }
        }
    }
}

void Board::RemoveOpponentDice(int col, int value)
{
    std::cout << "Checking opponent's board for dice to remove at column " << col << " with value " << value << std::endl;
    bool found = false;
    for (int row = 0; row < 3; ++row) {
        if (m_opponentBoard[row][col] == value) {
            m_opponentBoard[row][col] = 0;
            found = true;
            NotifyOnBoardUpdate();
            std::cout << "Removed dice at row " << row << std::endl;
        }
    }
    if (!found) {
        std::cout << "No dice found to remove." << std::endl;
    }
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
    for (const auto& row : m_board)
    {
        for (const auto& cell : row)
        {
            if (cell == 0)
            {
                return false;
            }
        }
    }
    return true;
}

const std::vector<std::vector<int>>& Board::GetBoard() const
{
    return m_board;
}

void Board::NotifyMove()
{
    NotifyOnBoardUpdate();
}