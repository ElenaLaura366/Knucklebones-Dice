#include "StartWindow.h"

#include "GameWindow.h"


StartWindow::StartWindow(GameState&& gameState, QWidget* parent)
	: QMainWindow(parent)
	, m_gameState(std::move(gameState))
{
	setWindowTitle("Start");
	resize(400, 300);

	m_uiStartButton = new QPushButton("Play", this);
	m_uiStartButton->setGeometry(150, 130, 100, 50);
	connect(m_uiStartButton, &QPushButton::clicked, this, &StartWindow::startGame);
}

void StartWindow::startGame()
{
	GameWindow* gameWindow = new GameWindow(std::move(m_gameState), 20);
	gameWindow->setAttribute(Qt::WA_DeleteOnClose);
	gameWindow->show();

	close();
}
