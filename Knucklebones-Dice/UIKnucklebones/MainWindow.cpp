#include "MainWindow.h"

#include "StartWidget.h"
#include "GameWidget.h"


MainWindow::MainWindow(Game&& game, QWidget* parent)
	: QMainWindow(parent)
{
	// make window fullscreen
	showMaximized();

	StartWidget* startWidget = new StartWidget(std::move(game), this);
	setCentralWidget(startWidget);
}
