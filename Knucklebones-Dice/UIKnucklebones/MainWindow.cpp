#include "MainWindow.h"

#include "StartWidget.h"
#include "GameWidget.h"


MainWindow::MainWindow(GameState&& gameState, QWidget* parent)
	: QMainWindow(parent)
{
	// make window fullscreen
	showMaximized();

	StartWidget* startWidget = new StartWidget(std::move(gameState), this);
	setCentralWidget(startWidget);
}
