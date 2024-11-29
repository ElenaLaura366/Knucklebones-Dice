#pragma once
#include "IGameListener.h"
#include "Player.h"
#include <vector>
#include <iostream>

class ScoreTracker : public IGameListener
{
public:
    void AddPlayer(const std::shared_ptr<Player>& player);
    void OnBoardUpdate() override;
    void OnGameOver() override;

    void DisplayScores() const;

private:
    std::vector<std::shared_ptr<Player>> m_players;
};
