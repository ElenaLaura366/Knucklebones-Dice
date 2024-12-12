#include "MainWindow.h"

#include "StartWidget.h"
#include "GameWidget.h"


MainWindow::MainWindow(Game&& game, QWidget* parent)
	: QMainWindow(parent)
{
	StartWidget* startWidget = new StartWidget(std::move(game), this);
	setCentralWidget(startWidget);

	// make window fullscreen
	showMaximized();
}
