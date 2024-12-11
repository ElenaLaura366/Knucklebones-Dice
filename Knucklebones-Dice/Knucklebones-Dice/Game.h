#pragma once

#include "IGameListener.h"
#include "BasicObservable.h"
#include "Board.h"
#include "Player.h"


class Game : public IObservable
{
public:
	Game(std::string_view namePlayer1, std::string_view namePlayer2);
	Game(Game&&) = default;

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;

	void MakeMove(int col, int value);

	Player& GetActivePlayer();
	Player& GetOpponentPlayer();
	const Player& GetActivePlayer() const;
	const Player& GetOpponentPlayer() const;

	const Player& GetPlayer1() const;
	const Player& GetPlayer2() const;

	Board& GetActiveBoard();
	Board& GetOpponentBoard();
	const Board& GetActiveBoard() const;
	const Board& GetOpponentBoard() const;

	const Board& GetPlayer1Board() const;
	const Board& GetPlayer2Board() const;

	bool IsGameOver();

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

	BasicObservable m_observableComponent;
};

