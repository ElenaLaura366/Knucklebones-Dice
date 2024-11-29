#include "UIKnucklebones.h"

UIKnucklebones::UIKnucklebones(QWidget* parent)
    : QMainWindow(parent),
    uigameWindow(nullptr)
{
    setWindowTitle("Start");
    resize(400, 300);

    startButton = new QPushButton("Play", this);
    startButton->setGeometry(150, 130, 100, 50);
    connect(startButton, &QPushButton::clicked, this, &UIKnucklebones::startGame);
}

UIKnucklebones::~UIKnucklebones()
{
    if (uigameWindow) {
        delete uigameWindow;
        uigameWindow = nullptr;
    }
}

void UIKnucklebones::startGame()
{
    if (!uigameWindow) {
        uigameWindow = new UIGameWindow(this);
    }
    else {
        uigameWindow->deleteLater();
        uigameWindow = new UIGameWindow(this);
    }

    this->hide();
    uigameWindow->show();
}

void UIKnucklebones::closeEvent(QCloseEvent* event)
{
    if (uigameWindow) {
        uigameWindow->close();
        delete uigameWindow;
        uigameWindow = nullptr;
    }
    event->accept();
}
