#pragma once
#include "Player.h"
#include <vector>

class GameState
{
public:
    GameState();

    ~GameState();

    void addPlayer(const Player& player);
    void setActivePlayer(int playerIndex);
    Player getActivePlayer() const;

    void nextPlayer();

    bool isGameActive() const;
    void endGame();
    bool checkGameOver(int winningScore); 

    Player getWinner() const;

private:
    std::vector<Player> m_players; 
    int m_activePlayerIndex;   
    bool m_gameActive;    
};
