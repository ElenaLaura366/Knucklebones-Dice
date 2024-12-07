#include "Player.h"


Player::Player(std::string_view name)
	: m_name(name)
	, m_score(0)
{
	// empty
}

void Player::OnBoardUpdate()
{
	UpdateScore(1);
}

void Player::OnGameOver()
{
	std::cout << "Player " << m_name << " - Final Score: " << m_score << "\n";
}

std::string_view Player::GetName() const
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
