#include "Player.h"

Player::Player(const std::string& name) : m_name(name), m_score(0) {}

void Player::OnBoardUpdate() 
{
    UpdateScore(1);
}

void Player::OnGameOver() 
{
    std::cout << "Player " << m_name << " - Final Score: " << m_score << "\n";
}

std::string Player::GetName() const 
{
    return m_name;
}

int Player::GetScore() const 
{
    return m_score;
}

void Player::UpdateScore(int points) 
{
    m_score = points;
}