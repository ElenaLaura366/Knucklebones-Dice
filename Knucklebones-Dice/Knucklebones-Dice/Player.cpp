#include "Player.h"

void Player::OnBoardUpdate()
{
    std::cout << "Player " << m_name << " is notified about the board update.\n";
    UpdateScore(1); // Exemplu: creștem scorul la fiecare mutare
}

void Player::OnGameOver()
{
    std::cout << "Player " << m_name << " is notified that the game is over. Final score: " << m_score << "\n";
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
    m_score += points;
}
