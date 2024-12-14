#pragma once

#include "Game.h"

#include <QPushButton>
#include <QMainWindow>


namespace ui
{
	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		MainWindow(QWidget* parent = nullptr);
	};
}
