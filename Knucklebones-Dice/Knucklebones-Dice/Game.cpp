#include "Game.h"


game::Game::Game(std::string_view namePlayer1, std::string_view namePlayer2, std::unique_ptr<IOpponentDifficulty> opponentDifficulty, int boardRows, int boardCols, int maxValue)
	: m_player1(namePlayer1)
	, m_player2(namePlayer2)
	, m_board1(boardRows, boardCols)
	, m_board2(boardRows, boardCols)
	, m_maxValue(maxValue)
	, m_activePlayerIndex(0)
	, m_opponentDifficulty(std::move(opponentDifficulty))
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

game::Player& game::Game::GetActivePlayer()
{
	return (m_activePlayerIndex == 0) ? m_player1 : m_player2;
}

game::Player& game::Game::GetOpponentPlayer()
{
	return (m_activePlayerIndex == 0) ? m_player2 : m_player1;
}

const game::Player& game::Game::GetActivePlayer() const
{
	return (m_activePlayerIndex == 0) ? m_player1 : m_player2;
}

const game::Player& game::Game::GetOpponentPlayer() const
{
	return (m_activePlayerIndex == 0) ? m_player2 : m_player1;
}

const game::Player& game::Game::GetPlayer1() const
{
	return m_player1;
}

const game::Player& game::Game::GetPlayer2() const
{
	return m_player2;
}

game::Board& game::Game::GetActiveBoard()
{
	return (m_activePlayerIndex == 0) ? m_board1 : m_board2;
}

game::Board& game::Game::GetOpponentBoard()
{
	return (m_activePlayerIndex == 0) ? m_board2 : m_board1;
}

const game::Board& game::Game::GetActiveBoard() const
{
	return (m_activePlayerIndex == 0) ? m_board1 : m_board2;
}

const game::Board& game::Game::GetOpponentBoard() const
{
	return (m_activePlayerIndex == 0) ? m_board2 : m_board1;
}

const game::Board& game::Game::GetBoard1() const
{
	return m_board1;
}

const game::Board& game::Game::GetBoard2() const
{
	return m_board2;
}

int game::Game::GetRandomValue() const
{
	return std::rand() % m_maxValue + 1;
}

int game::Game::CalculateScore(int board) const
{
	if (board == 1)
	{
		return m_board1.CalculateTotalScore();
	}
	else if (board == 2)
	{
		return m_board2.CalculateTotalScore();
	}

	throw std::runtime_error("Board doesn't exist");
}

void game::Game::MakeMove(int col, int value)
{
	Board& activeBoard = GetActiveBoard();
	Board& opponentBoard = GetOpponentBoard();

	activeBoard.MakeMove(col, value);
	opponentBoard.CancelValuesInColumn(col, value);

	// Turn change
	m_activePlayerIndex = (m_activePlayerIndex + 1) % 2;

	if (m_opponentDifficulty && !IsGameOver())
	{
		Board& activeBoard = GetActiveBoard();
		Board& opponentBoard = GetOpponentBoard();

		int value = GetRandomValue();
		int col = m_opponentDifficulty->NextMove(activeBoard, opponentBoard, value);

		activeBoard.MakeMove(col, value);
		opponentBoard.CancelValuesInColumn(col, value);

		// Turn change
		m_activePlayerIndex = (m_activePlayerIndex + 1) % 2;
	}

	if (IsGameOver())
	{
		NotifyOnGameOver();
	}

	NotifyOnBoardUpdate();
}

bool game::Game::IsGameOver()
{
	if (m_board1.IsFull() || m_board2.IsFull())
	{
		return true;
	}
	return false;
}

void game::Game::AddListener(IGameListener* listener)
{
	m_observableComponent.AddListener(listener);
}

void game::Game::RemoveListener(IGameListener* listener)
{
	m_observableComponent.RemoveListener(listener);
}

void game::Game::NotifyOnBoardUpdate()
{
	m_observableComponent.NotifyOnBoardUpdate();
}

void game::Game::NotifyOnGameOver()
{
	m_observableComponent.NotifyOnGameOver();
}
