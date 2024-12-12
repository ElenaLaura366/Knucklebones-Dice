#include "MainWindow.h"

#include "StartWidget.h"
#include "GameWidget.h"


MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	StartWidget* startWidget = new StartWidget(this);
	setCentralWidget(startWidget);

	// make window fullscreen
	showMaximized();
}
