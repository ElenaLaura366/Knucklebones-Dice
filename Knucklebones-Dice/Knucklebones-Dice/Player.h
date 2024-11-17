#pragma once
#include "Board.h"
#include <string>

class Player
{
public:
	Player();
	~Player();

	void setPlayer(std::string name);
	std::string getPlayer();

	void setBoard(Board board);
	Board getBoard();
private:
	std::string m_player;
	Board m_board;
};