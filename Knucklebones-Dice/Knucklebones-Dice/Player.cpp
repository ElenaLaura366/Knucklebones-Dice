#include "Player.h"


Player::Player(std::string_view name)
	: m_name(name)
{
	// empty
}

void Player::OnBoardUpdate()
{
	// empty
}

void Player::OnGameOver()
{
	// empty
}

std::string_view Player::GetName() const
{
	return m_name;
}
