#include "Player.h"


Player::Player(std::string_view name)
	: m_name(name)
{
	// empty
}

std::string_view Player::GetName() const
{
	return m_name;
}
