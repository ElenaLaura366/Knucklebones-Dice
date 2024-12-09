#pragma once

#include "GameState.h"
#include "Player.h"

#include <QPushButton>
#include <QMainWindow>


class StartWindow : public QMainWindow
{
	Q_OBJECT

public:
	StartWindow(GameState&& gameState, QWidget* parent = nullptr);

private slots:
	void startGame();

private:
	QPushButton* m_uiStartButton = nullptr;

private:
	GameState m_gameState;
};
