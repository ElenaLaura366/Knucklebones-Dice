#pragma once

#include "IGameListener.h"
#include "BasicObservable.h"
#include "Board.h"
#include "Player.h"

#include <cstdlib>
#include <ctime>


class GameState : public IObservable
{
public:
	GameState(std::string_view namePlayer1, std::string_view namePlayer2);

	GameState(const GameState&) = delete;
	GameState& operator=(const GameState&) = delete;
	GameState(GameState&&) = default;
	GameState& operator=(GameState&&) = delete;

	void NextPlayer();
	Player& GetActivePlayer();
	const Player& GetActivePlayer() const;
	Player& GetOpponentPlayer();
	const Player& GetOpponentPlayer() const;

	const Player& GetPlayer1() const;
	const Player& GetPlayer2() const;

	Board& GetActiveBoard();
	Board& GetOpponentBoard();

	const Board& GetPlayer1Board() const;
	const Board& GetPlayer2Board() const;

	bool IsGameActive() const;

	void CheckForGameOver();
	void CancelMatchingDiceOnOpponentBoard(int col, int value);
	void UpdateScores();

	void AddListener(IGameListener* listener) override;
	void RemoveListener(IGameListener* listener) override;
	void NotifyOnBoardUpdate() override;
	void NotifyOnGameOver() override;

private:
	Player m_player1;
	Player m_player2;
	Board m_board1;
	Board m_board2;

	uint8_t m_activePlayerIndex;
	bool m_gameActive;

	BasicObservable m_observableComponent;
};

