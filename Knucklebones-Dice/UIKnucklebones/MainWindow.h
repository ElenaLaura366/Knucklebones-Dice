#pragma once

#include "Game.h"

#include <QPushButton>
#include <QMainWindow>


namespace ui
{
	/*!
	*	\brief The only window of the application (besides the dialog windows). It starts maximized.
	*/
	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		/*!
		*	\brief MainWindow constructor. Initializes a `ui::StartWidget` as the starting content widget.
		*/
		MainWindow(QWidget* parent = nullptr);
	};
}
