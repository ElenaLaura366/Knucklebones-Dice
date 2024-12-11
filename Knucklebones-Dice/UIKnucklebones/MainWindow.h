#pragma once

#include "Game.h"

#include <QPushButton>
#include <QMainWindow>


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(Game&& game, QWidget* parent = nullptr);
};
