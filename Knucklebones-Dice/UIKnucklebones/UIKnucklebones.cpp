#include "UIKnucklebones.h"

UIKnucklebones::UIKnucklebones(GameState&& gameState, QWidget* parent)
	: QMainWindow(parent)
	, m_uiGameWindow(nullptr)
	, m_gameState(std::move(gameState))
{
	setWindowTitle("Start");
	resize(400, 300);

	startButton = new QPushButton("Play", this);
	startButton->setGeometry(150, 130, 100, 50);
	connect(startButton, &QPushButton::clicked, this, &UIKnucklebones::startGame);
}

void UIKnucklebones::startGame()
{
	m_uiGameWindow = std::make_unique<UIGameWindow>(std::move(m_gameState), 20);
	this->hide();
	m_uiGameWindow->show();
}

void UIKnucklebones::closeEvent(QCloseEvent* event)
{
	if (m_uiGameWindow)
	{
		m_uiGameWindow->close();
		m_uiGameWindow.reset();
	}
	event->accept();
}
