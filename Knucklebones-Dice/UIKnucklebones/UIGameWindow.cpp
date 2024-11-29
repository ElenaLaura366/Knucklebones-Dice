#include "UIGameWindow.h"

UIGameWindow::UIGameWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Knucklebones Dice");
    resize(800, 600);
}
