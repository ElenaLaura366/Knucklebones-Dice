﻿#pragma once

#include "IGameListener.h"
#include "IOpponentDifficulty.h"
#include "BasicObservable.h"
#include "Board.h"
#include "Player.h"


class Game : public IObservable
{
public:
	Game(std::string_view namePlayer1, std::string_view namePlayer2,
		std::unique_ptr<IOpponentDifficulty> opponentDifficulty,
		int boardRows = Board::DefaultRows, int boardCols = Board::DefaultCols, int maxValue = Game::DefaultMaxValue);
	Game(Game&&) = default;

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;

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

