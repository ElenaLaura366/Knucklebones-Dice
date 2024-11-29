#pragma once

#include "IGameListener.h"
#include <string>
#include <iostream>

class Player : public IGameListener
{
public:
    Player(const std::string& name) : m_name(name), m_score(0) {}

    void OnBoardUpdate() override;
    void OnGameOver() override;

    std::string GetName() const;
    int GetScore() const;

    void UpdateScore(int points);

private:
    std::string m_name;
    int m_score;
};
