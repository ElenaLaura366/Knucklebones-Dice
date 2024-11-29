#include "UIGameWindow.h"

UIGameWindow::UIGameWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Knucklebones Dice");
    resize(800, 600);
}

void UIGameWindow::closeEvent(QCloseEvent* event)
{
    QApplication::quit();
    event->accept();
}