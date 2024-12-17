#include "StartWidget.h"

#include "MainWindow.h"
#include "GameWidget.h"
#include "EasyDifficulty.h"
#include "HardDifficulty.h"

#include <QPropertyAnimation>
#include <QStyle>


ui::StartWidget::StartWidget(MainWindow* parent)
	: BaseMainWidget(parent)
	, m_gameMode(GameMode::None)
{
	GetParentWindow()->setWindowTitle("Select Game Mode");

	m_selectMultiplayer = new QPushButton("Multiplayer", this);
	m_selectPC = new QPushButton("Play vs PC", this);
	m_selectEasy = new QPushButton("Easy", this);
	m_selectHard = new QPushButton("Hard", this);
	m_startButton = new QPushButton("Play", this);

	QSize buttonSize(150, 50);
	m_selectMultiplayer->setMinimumSize(buttonSize);
	m_selectPC->setMinimumSize(buttonSize);
	m_selectEasy->setMinimumSize(buttonSize);
	m_selectHard->setMinimumSize(buttonSize);
	m_startButton->setMinimumSize(buttonSize);

	m_selectEasy->setEnabled(false);
	m_selectHard->setEnabled(false);
	m_startButton->setEnabled(false);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setAlignment(Qt::AlignCenter);

	QLabel* instructionLabel = new QLabel("Select Game Mode:");
	instructionLabel->setAlignment(Qt::AlignCenter);

	mainLayout->addWidget(instructionLabel);
	mainLayout->addWidget(m_selectMultiplayer);
	mainLayout->addWidget(m_selectPC);

	m_difficultyLabel = new QLabel("Select Difficulty:");
	m_difficultyLabel->setAlignment(Qt::AlignCenter);
	m_difficultyLabel->setVisible(false);
	mainLayout->addWidget(m_difficultyLabel);
	mainLayout->addWidget(m_selectEasy);
	mainLayout->addWidget(m_selectHard);

	mainLayout->addWidget(m_startButton);

	connect(m_selectMultiplayer, &QPushButton::clicked, this, [this]() {
		m_gameMode = GameMode::Multiplayer;
		m_selectEasy->setEnabled(false);
		m_selectHard->setEnabled(false);
		m_difficultyLabel->setVisible(false);
		m_startButton->setEnabled(true);

		SetProperty(m_selectMultiplayer, Property::QButton_selected, true);
		SetProperty({ m_selectPC, m_selectEasy, m_selectHard }, Property::QButton_selected, false);
		});

	connect(m_selectPC, &QPushButton::clicked, this, [this]() {
		m_gameMode = GameMode::None;
		m_selectEasy->setEnabled(true);
		m_selectHard->setEnabled(true);
		m_difficultyLabel->setVisible(true);
		m_startButton->setEnabled(false);

		SetProperty(m_selectPC, Property::QButton_selected, true);
		SetProperty({ m_selectMultiplayer, m_selectEasy, m_selectHard }, Property::QButton_selected, false);
		});

	connect(m_selectEasy, &QPushButton::clicked, this, [this]() {
		m_gameMode = GameMode::PC_Easy;
		m_startButton->setEnabled(true);

		SetProperty(m_selectEasy, Property::QButton_selected, true);
		SetProperty(m_selectHard, Property::QButton_selected, false);
		});

	connect(m_selectHard, &QPushButton::clicked, this, [this]() {
		m_gameMode = GameMode::PC_Hard;
		m_startButton->setEnabled(true);

		SetProperty(m_selectEasy, Property::QButton_selected, false);
		SetProperty(m_selectHard, Property::QButton_selected, true);
		});

	connect(m_startButton, &QPushButton::clicked, this, &StartWidget::StartGame);
}


void ui::StartWidget::StartGame()
{
	std::unique_ptr<game::IOpponentDifficulty> difficulty = nullptr;
	if (m_gameMode == GameMode::PC_Easy)
	{
		difficulty = std::make_unique<game::EasyDifficulty>();
	}
	else if (m_gameMode == GameMode::PC_Hard)
	{
		difficulty = std::make_unique<game::HardDifficulty>();
	}

	game::Game game("Player 1", "Player 2", std::move(difficulty));
	GameWidget* gameWidget = new GameWidget(std::move(game), 10, GetParentWindow());
	GetParentWindow()->setCentralWidget(gameWidget);
	deleteLater();
}
