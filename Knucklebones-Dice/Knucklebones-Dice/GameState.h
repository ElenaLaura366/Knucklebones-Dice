#pragma once
#include "IGameListener.h"
#include "Observable.h"
#include "Board.h"
#include "Player.h"
#include <cstdlib>
#include <ctime>

class GameState : public Observable 
{
public:
    GameState();

    void AddPlayer(Player& player);
    void NextPlayer();
    Player& GetActivePlayer();
    Player& GetOpponentPlayer();

    Board& GetActiveBoard();
    Board& GetOpponentBoard();

    int RollDice();
    bool IsGameActive() const;

private:
    std::vector<Player*> m_players;
    Board m_player1Board;
    Board m_player2Board;
    int m_activePlayerIndex = 0;
    bool m_gameActive = true;

    void NotifyGameStateChange();
};
