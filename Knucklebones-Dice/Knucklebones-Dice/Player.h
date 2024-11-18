#pragma once
#include "Board.h"
#include <string>

class Player
{
public:
    Player();
    Player(const std::string& name, const Board& board);

    ~Player();

    void setPlayer(const std::string& name);
    std::string getPlayer() const;

    void setBoard(const Board& board);
    Board getBoard() const;

    void setScore(int score);
    int getScore() const;

    void updateScore(int points); 
    void resetScore();     

private:
    std::string m_player;  
    Board m_board;         
    int m_score = 0;       
};
