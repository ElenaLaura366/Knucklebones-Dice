#pragma once

#include "GameState.h"
#include "Player.h"

#include <QPushButton>
#include <QMainWindow>


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(GameState&& gameState, QWidget* parent = nullptr);
};
