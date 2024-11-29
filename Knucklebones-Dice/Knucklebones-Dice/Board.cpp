#include "Board.h"

Board::Board() : m_board(3, std::vector<int>(3, 0)) {}

void Board::MakeMove(int col, int value)
{
    if (!IsColumnFull(col)) {
        for (int row = 0; row < 3; ++row) {
            if (m_board[row][col] == 0) {
                m_board[row][col] = value;
                NotifyMove(); // Notificăm observatorii că a fost făcută o mutare
                break;
            }
        }
    }
}

bool Board::IsColumnFull(int col) const
{
    for (int row = 0; row < 3; ++row) {
        if (m_board[row][col] == 0) {
            return false;
        }
    }
    return true;
}

bool Board::IsFull() const
{
    for (const auto& row : m_board) {
        for (const auto& cell : row) {
            if (cell == 0) {
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
    NotifyOnBoardUpdate(); // Notificăm toți observatorii că tabla a fost actualizată
}