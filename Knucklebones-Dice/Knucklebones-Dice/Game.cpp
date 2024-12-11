#include "Game.h"


Game::Game(std::string_view namePlayer1, std::string_view namePlayer2)
	: m_player1(namePlayer1)
	, m_player2(namePlayer2)
	, m_board1()
	, m_board2()
	, m_activePlayerIndex(0)
	, m_gameActive(true)
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Game::NextPlayer()
{
	m_activePlayerIndex = (m_activePlayerIndex + 1) % 2;
}

const Player& Game::GetPlayer1() const
{
	return m_player1;
}

const Player& Game::GetPlayer2() const
{
	return m_player2;
}

Player& Game::GetActivePlayer()
{
	return (m_activePlayerIndex == 0) ? m_player1 : m_player2;
}

const Player& Game::GetActivePlayer() const
{
	return (m_activePlayerIndex == 0) ? m_player1 : m_player2;
}

Player& Game::GetOpponentPlayer()
{
	return (m_activePlayerIndex == 0) ? m_player2 : m_player1;
}

const Player& Game::GetOpponentPlayer() const
{
	return (m_activePlayerIndex == 0) ? m_player2 : m_player1;
}

const Board& Game::GetPlayer1Board() const
{
	return m_board1;
}

const Board& Game::GetPlayer2Board() const
{
	return m_board2;
}

Board& Game::GetActiveBoard()
{
	return (m_activePlayerIndex == 0) ? m_board1 : m_board2;
}

Board& Game::GetOpponentBoard()
{
	return (m_activePlayerIndex == 0) ? m_board2 : m_board1;
}

bool Game::IsGameActive() const
{
	return m_gameActive;
}

void Game::CheckForGameOver()
{
	if (m_board1.IsFull() || m_board2.IsFull())
	{
		m_gameActive = false;
		NotifyOnGameOver();
	}
}

void Game::CancelMatchingDiceOnOpponentBoard(int col, int value)
{
	Board& opponentBoard = GetOpponentBoard();
	opponentBoard.CancelValuesInColumn(col, value);
}

void Game::UpdateScores()
{
	m_player1.UpdateScore(m_board1.CalculateTotalScore());
	m_player2.UpdateScore(m_board2.CalculateTotalScore());
}

void Game::AddListener(IGameListener* listener)
{
	m_observableComponent.AddListener(listener);
}

void Game::RemoveListener(IGameListener* listener)
{
	m_observableComponent.RemoveListener(listener);
}

void Game::NotifyOnBoardUpdate()
{
	m_observableComponent.NotifyOnBoardUpdate();
}

void Game::NotifyOnGameOver()
{
	m_observableComponent.NotifyOnGameOver();
}
