#pragma once
#include "Board.h"
#include "Player.h"
#include <string>
#include <vector>
#include <algorithm>

class ScoreTracker
{
public:
	ScoreTracker();
	~ScoreTracker();

	std::pair<int, int> evaluateScore(const Board& board);
	void updateScore(Player& player);
	int getWinnerIndex(const std::vector<Player>& players) const;
	void displayScores(const std::vector<Player>& players) const;

private:
	std::vector<Board> m_board;
};