#pragma once

#include "BaseMainWidget.h"
#include "Game.h"

#include <QPushButton>
#include <QMainWindow>


class StartWidget : public BaseMainWidget
{
	Q_OBJECT

public:
	StartWidget(Game&& game, MainWindow* parent);

private slots:
	void StartGame();

private:
	Game m_game;
};
