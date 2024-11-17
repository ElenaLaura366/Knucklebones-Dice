#pragma once
#include "Board.h"
#include "Player.h"
#include <string>
#include <vector>

class ScoreTracker
{
public:
	ScoreTracker();
	~ScoreTracker();

	std::pair<int,int> evaluateScore(int indexPlayer, int move);
private:
	std::vector<Board> m_board;
};