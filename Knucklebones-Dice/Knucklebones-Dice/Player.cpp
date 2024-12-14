﻿#include "Player.h"


game::Player::Player(std::string_view name)
	: m_name(name)
{
	// empty
}

std::string_view game::Player::GetName() const
{
	return m_name;
}
