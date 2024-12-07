#pragma once

#include "IGameListener.h"

#include <string>
#include <iostream>


class Player : public IGameListener
{
public:
	Player(std::string_view name);
	Player(Player&&) = default;

	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	Player& operator=(Player&&) = delete;

	void OnBoardUpdate() override;
	void OnGameOver() override;

	std::string_view GetName() const;
	int GetScore() const;

	void UpdateScore(int points);

private:
	std::string m_name;
	int m_score;
};
