#include "StartWidget.h"

#include "MainWindow.h"
#include "GameWidget.h"


StartWidget::StartWidget(GameState&& gameState, MainWindow* parent)
	: BaseMainWidget(parent)
	, m_gameState(std::move(gameState))
{
	GetParentWindow()->setWindowTitle("Start");

	m_uiStartButton = new QPushButton("Play", this);
	m_uiStartButton->setGeometry(150, 130, 100, 50);
	connect(m_uiStartButton, &QPushButton::clicked, this, &StartWidget::startGame);
}

void StartWidget::startGame()
{
	GameWidget* gameWidget = new GameWidget(std::move(m_gameState), 20, GetParentWindow());
	GetParentWindow()->setCentralWidget(gameWidget);
}
