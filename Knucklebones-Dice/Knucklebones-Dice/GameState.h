#pragma once
#include "IGameListener.h"
#include "Observable.h"
#include "Board.h"
#include "Player.h"
#include <memory>
#include <cstdlib>
#include <ctime>

class GameState : public IGameListener, public Observable
{
public:
    GameState(std::shared_ptr<Board> board);

    void AddPlayer(const std::shared_ptr<Player>& player);
    void NextPlayer();
    const std::shared_ptr<Player>& GetActivePlayer() const;

    void OnBoardUpdate() override;
    void OnGameOver() override;

    bool IsGameActive() const;

    int RollDice();

private:
    std::vector<std::shared_ptr<Player>> m_players;
    std::shared_ptr<Board> m_board;
    int m_activePlayerIndex = 0;
    bool m_gameActive = true;

    void CheckGameOver();
};
