#pragma once

#include "BaseMainWidget.h"
#include "GameState.h"

#include <QPushButton>
#include <QMainWindow>


class StartWidget : public BaseMainWidget
{
	Q_OBJECT

public:
	StartWidget(GameState&& gameState, MainWindow* parent);

private slots:
	void startGame();

private:
	QPushButton* m_uiStartButton = nullptr;

private:
	GameState m_gameState;
};