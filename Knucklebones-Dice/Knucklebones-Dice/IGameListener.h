#pragma once

#include <memory>


class IGameListener
{
public:
	virtual ~IGameListener() = default;
	virtual void OnBoardUpdate() = 0;
	virtual void OnGameOver() = 0;
};
