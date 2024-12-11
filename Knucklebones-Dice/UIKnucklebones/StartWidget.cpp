#include "StartWidget.h"

#include "MainWindow.h"
#include "GameWidget.h"

#include <QPropertyAnimation>


StartWidget::StartWidget(Game&& game, MainWindow* parent)
	: BaseMainWidget(parent)
	, m_game(std::move(game))
{
	GetParentWindow()->setWindowTitle("Start");
	QPushButton* startButton = new QPushButton("Play", this);
	startButton->setFixedSize(100, 50);

	QBoxLayout* layout = new QHBoxLayout(this);
	layout->addStretch(1);
	layout->addWidget(startButton);
	layout->addStretch(1);

	setLayout(layout);

	connect(startButton, &QPushButton::clicked, this, &StartWidget::StartGame);
}

void StartWidget::StartGame()
{
	/*QPropertyAnimation* animation = new QPropertyAnimation(this, "windowOpacity");
	animation->setDuration(1000);
	animation->setStartValue(1.0);
	animation->setEndValue(0.0);
	animation->start(QAbstractAnimation::DeleteWhenStopped);

	connect(animation, &QPropertyAnimation::finished, this, [this]() {
		GameWidget* gameWidget = new GameWidget(std::move(m_game), 20, GetParentWindow());
		GetParentWindow()->setCentralWidget(gameWidget);
		deleteLater();
		});*/

	GameWidget* gameWidget = new GameWidget(std::move(m_game), 20, GetParentWindow());
	GetParentWindow()->setCentralWidget(gameWidget);
	deleteLater();
}
