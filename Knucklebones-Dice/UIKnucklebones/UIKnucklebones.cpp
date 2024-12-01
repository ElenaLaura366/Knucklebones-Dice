#include "UIKnucklebones.h"

UIKnucklebones::UIKnucklebones(GameState& gameState, Player& player1, Player& player2, QWidget* parent)
    : QMainWindow(parent),
    uigameWindow(nullptr),
    m_gameState(gameState),
    m_player1(player1),
    m_player2(player2) {
    setWindowTitle("Start");
    resize(400, 300);

    startButton = new QPushButton("Play", this);
    startButton->setGeometry(150, 130, 100, 50);
    connect(startButton, &QPushButton::clicked, this, &UIKnucklebones::startGame);
}

UIKnucklebones::~UIKnucklebones() 
{
    if (uigameWindow) 
    {
        delete uigameWindow;
        uigameWindow = nullptr;
    }
}

void UIKnucklebones::startGame() 
{
    if (!uigameWindow) 
    {
        uigameWindow = new UIGameWindow(m_gameState, m_player1, m_player2, this);
    }
    else {
        delete uigameWindow;
        uigameWindow = new UIGameWindow(m_gameState, m_player1, m_player2, this);
    }

    this->hide();
    uigameWindow->show();
}

void UIKnucklebones::closeEvent(QCloseEvent* event) 
{
    if (uigameWindow) 
    {
        uigameWindow->close();
        delete uigameWindow;
        uigameWindow = nullptr;
    }
    event->accept();
}
