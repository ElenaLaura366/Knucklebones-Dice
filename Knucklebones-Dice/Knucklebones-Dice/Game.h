#pragma once

#include "IGameListener.h"
#include "IOpponentDifficulty.h"
#include "BasicObservable.h"
#include "Board.h"
#include "Player.h"

/*!
	Class responsible of handling the game logic.
*/
class Game : public IObservable
{
public:
	//! Game class constructor
	/*! 
	*	\brief Takes the player names, the difficulty, board size and maximum number to roll.
	*	\param namePlayer1 sets the name of the first player.
	*	\param namePlayer2 sets the name of the second player.
	*	\param opponentDifficulty sets the difficulty of the game played.
	*	If null the game will be set on multiplayer mode - 2 players, 
	*	otherwise the computer will take the role of the second player.
	*	\param boardRows sets the number of rows the board will have.
	*	If not specified, it will be set on 3.
	*	\param boardCols sets the number of columns the board will have.
	*	If not specified, it will be set on 3.
	*	\param maxValue sets the maximum value a palyer can roll.
	*	If not specified, it will be set on 6.
	*/
	Game(std::string_view namePlayer1, std::string_view namePlayer2,
		std::unique_ptr<IOpponentDifficulty> opponentDifficulty,
		int boardRows = Board::DefaultRows, int boardCols = Board::DefaultCols, int maxValue = Game::DefaultMaxValue);
	Game(Game&&) = default;

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;

	//! Handles the move of a player/computer
	/*! 
	*	Takes as input the place of the move and make it, if it is valid.
	*	\brief It will also switch the active player.
	*	\brief If the game mode is set on singleplayer, (player vs computer) the computer will follow with its move.
	*	\param col is the index of the column.
	*	\param value is the value the player rolled.
	*	\sa Board::MakeMove
	*	\sa GetRandomValue
	*	\sa EasyDifficulty::NextMove
	*	\sa HardDifficulty::NextMove
	*	\sa NotifyOnGameOver
	*/
	void MakeMove(int col, int value);

	const Player& GetActivePlayer() const;
	const Player& GetOpponentPlayer() const;

	const Player& GetPlayer1() const;
	const Player& GetPlayer2() const;

	const Board& GetActiveBoard() const;
	const Board& GetOpponentBoard() const;

	const Board& GetBoard1() const;
	const Board& GetBoard2() const;

	int GetRandomValue() const;

	int CalculateScore(int board) const;

	void AddListener(IGameListener* listener) override;
	void RemoveListener(IGameListener* listener) override;
	void NotifyOnBoardUpdate() override;
	void NotifyOnGameOver() override;

private:
	Player& GetActivePlayer();
	Player& GetOpponentPlayer();

	Board& GetActiveBoard();
	Board& GetOpponentBoard();

	bool IsGameOver();

public:
	static constexpr int DefaultMaxValue = 6;

private:
	Player m_player1;
	Player m_player2;
	Board m_board1;
	Board m_board2;

	uint8_t m_activePlayerIndex;
	int m_maxValue;

	BasicObservable m_observableComponent;
	std::unique_ptr<IOpponentDifficulty> m_opponentDifficulty;
};

