#pragma once

#include "IGameListener.h"

#include <vector>
#include <memory>
#include <iostream>


class Game
{
public:
	void MakeMove(int col, int value);

	int GetMoves() const;
	void EndGame();

	void AddListener(IGameListener* listener);
	void RemoveListener(IGameListener* listener);

private:
	int m_moves = 0;
	bool m_gameActive = true;
	std::vector<IGameListener*> m_listeners;

	void NotifyOnBoardUpdate();
	void NotifyOnGameOver();
};
