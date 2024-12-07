#include "GameState.h"


GameState::GameState(std::string_view namePlayer1, std::string_view namePlayer2)
	: m_player1(namePlayer1)
	, m_player2(namePlayer2)
	, m_board1()
	, m_board2()
	, m_activePlayerIndex(0)
	, m_gameActive(true)
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void GameState::NextPlayer()
{
	m_activePlayerIndex = (m_activePlayerIndex + 1) % 2;
}

const Player& GameState::GetPlayer1() const
{
	return m_player1;
}

const Player& GameState::GetPlayer2() const
{
	return m_player2;
}

Player& GameState::GetActivePlayer()
{
	return (m_activePlayerIndex == 0) ? m_player1 : m_player2;
}

Player& GameState::GetOpponentPlayer()
{
	return (m_activePlayerIndex == 0) ? m_player2 : m_player1;
}

const Board& GameState::GetPlayer1Board() const
{
	return m_board1;
}

const Board& GameState::GetPlayer2Board() const
{
	return m_board2;
}

Board& GameState::GetActiveBoard()
{
	return (m_activePlayerIndex == 0) ? m_board1 : m_board2;
}

Board& GameState::GetOpponentBoard()
{
	return (m_activePlayerIndex == 0) ? m_board2 : m_board1;
}

bool GameState::IsGameActive() const
{
	return m_gameActive;
}

void GameState::CheckForGameOver()
{
	if (m_board1.IsFull() || m_board2.IsFull())
	{
		m_gameActive = false;
		NotifyOnGameOver();
	}
}

void GameState::CancelMatchingDiceOnOpponentBoard(int col, int value)
{
	Board& opponentBoard = GetOpponentBoard();
	opponentBoard.CancelValuesInColumn(col, value);
}

void GameState::UpdateScores()
{
	m_player1.UpdateScore(m_board1.CalculateTotalScore());
	m_player2.UpdateScore(m_board2.CalculateTotalScore());
}
