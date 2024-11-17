#pragma once
#include <string>
#include <vector>

class Board
{
public:
	Board();
	~Board();

	void Update();

	void setPlayer(std::string name);
	std::string getPlayer();

	//void setBoard(int row, int col, int value);
	std::vector<std::vector<int>> getBoard(int row, int col);

	void makeMove(int col, int value);
	int boardScore();
private:
	std::string m_player;
	std::vector<std::vector<int>> m_board;

};