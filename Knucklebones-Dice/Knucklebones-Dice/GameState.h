#pragma once

#include "IGameListener.h"
#include "Board.h"
#include "Player.h"
#include <vector>
#include <memory>

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

private:
    std::vector<std::shared_ptr<Player>> m_players;
    std::shared_ptr<Board> m_board;
    int m_activePlayerIndex = 0;
    bool m_gameActive = true;

    void CheckGameOver(); // Verifică dacă jocul s-a încheiat
};
