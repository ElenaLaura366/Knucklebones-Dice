#include "Game.h"


Game::Game(std::string_view namePlayer1, std::string_view namePlayer2, std::unique_ptr<IOpponentDifficulty> opponentDifficulty)
	: m_player1(namePlayer1)
	, m_player2(namePlayer2)
	, m_board1()
	, m_board2()
	, m_activePlayerIndex(0)
	, m_opponentDifficulty(std::move(opponentDifficulty))
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

Player& Game::GetActivePlayer()
{
	return (m_activePlayerIndex == 0) ? m_player1 : m_player2;
}

Player& Game::GetOpponentPlayer()
{
	return (m_activePlayerIndex == 0) ? m_player2 : m_player1;
}

const Player& Game::GetActivePlayer() const
{
	return (m_activePlayerIndex == 0) ? m_player1 : m_player2;
}

const Player& Game::GetOpponentPlayer() const
{
	return (m_activePlayerIndex == 0) ? m_player2 : m_player1;
}

const Player& Game::GetPlayer1() const
{
	return m_player1;
}

const Player& Game::GetPlayer2() const
{
	return m_player2;
}

Board& Game::GetActiveBoard()
{
	return (m_activePlayerIndex == 0) ? m_board1 : m_board2;
}

Board& Game::GetOpponentBoard()
{
	return (m_activePlayerIndex == 0) ? m_board2 : m_board1;
}

const Board& Game::GetActiveBoard() const
{
	return (m_activePlayerIndex == 0) ? m_board1 : m_board2;
}

const Board& Game::GetOpponentBoard() const
{
	return (m_activePlayerIndex == 0) ? m_board2 : m_board1;
}

const Board& Game::GetBoard1() const
{
	return m_board1;
}

const Board& Game::GetBoard2() const
{
	return m_board2;
}

int Game::CalculateScore(int board) const
{
	if (board == 1)
	{
		return m_board1.CalculateTotalScore();
	}
	else if (board == 2)
	{
		return m_board2.CalculateTotalScore();
	}

	throw std::runtime_error(std::string("Board ( ") + std::to_string(board) + " ) does not exist");
}

void Game::MakeMove(int col, int value)
{
	GetActiveBoard().MakeMove(col, value);

	Board& opponentBoard = GetOpponentBoard();
	opponentBoard.CancelValuesInColumn(col, value);

	m_activePlayerIndex = (m_activePlayerIndex + 1) % 2;

	if (m_opponentDifficulty && !IsGameOver())
	{
		int value = std::rand() % 6 + 1;
		int col = m_opponentDifficulty->NextMove(GetActiveBoard(), GetOpponentBoard(), value);
		GetActiveBoard().MakeMove(col, value);

		Board& opponentBoard = GetOpponentBoard();
		opponentBoard.CancelValuesInColumn(col, value);

		m_activePlayerIndex = (m_activePlayerIndex + 1) % 2;
	}

	if (IsGameOver())
	{
		NotifyOnGameOver();
	}

	NotifyOnBoardUpdate();
}

bool Game::IsGameOver()
{
	if (m_board1.IsFull() || m_board2.IsFull())
	{
		return true;
	}
	return false;
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
