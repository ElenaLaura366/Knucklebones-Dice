#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::setPlayer(std::string name)
{
	this->m_player = name;
}

std::string Player::getPlayer()
{
	return this->m_player;
}

void Player::setBoard(Board board)
{
	this->m_board = board;
}

Board Player::getBoard()
{
	return this->m_board;
}
