#include "StartWidget.h"

#include "MainWindow.h"
#include "GameWidget.h"
#include <EasyDifficulty.h>
#include <HardDifficulty.h>
#include <QPropertyAnimation>
StartWidget::StartWidget(Game&& game, MainWindow* parent)
    : BaseMainWidget(parent)
    , m_game(std::move(game))
    , m_selectedMode("")
{
    GetParentWindow()->showMaximized();
    GetParentWindow()->setWindowTitle("Select Game Mode");

    m_selectMultiplayer = new QPushButton("Multiplayer", this);
    m_selectPC = new QPushButton("Play vs PC", this);
    m_selectEasy = new QPushButton("Easy", this);
    m_selectHard = new QPushButton("Hard", this);
    m_startButton = new QPushButton("Play", this);

    QSize buttonSize(150, 50); 
    m_selectMultiplayer->setFixedSize(buttonSize);
    m_selectPC->setFixedSize(buttonSize);
    m_selectEasy->setFixedSize(buttonSize);
    m_selectHard->setFixedSize(buttonSize);
    m_startButton->setFixedSize(buttonSize);

    m_selectEasy->setEnabled(false);
    m_selectHard->setEnabled(false);
    m_startButton->setEnabled(false);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QLabel* instructionLabel = new QLabel("Select Game Mode:");
    instructionLabel->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(instructionLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(m_selectMultiplayer, 0, Qt::AlignCenter);
    mainLayout->addWidget(m_selectPC, 0, Qt::AlignCenter);

    m_difficultyLabel = new QLabel("Select Difficulty:");
    m_difficultyLabel->setAlignment(Qt::AlignCenter);
    m_difficultyLabel->setVisible(false);
    mainLayout->addWidget(m_difficultyLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(m_selectEasy, 0, Qt::AlignCenter);
    mainLayout->addWidget(m_selectHard, 0, Qt::AlignCenter);

    mainLayout->addWidget(m_startButton, 0, Qt::AlignCenter);
    setLayout(mainLayout);

    connect(m_selectMultiplayer, &QPushButton::clicked, this, [this]() {
        m_selectedMode = "Multiplayer";
        m_selectEasy->setEnabled(false);
        m_selectHard->setEnabled(false);
        m_difficultyLabel->setVisible(false);
        m_startButton->setEnabled(true);
        });

    connect(m_selectPC, &QPushButton::clicked, this, [this]() {
        m_selectedMode = "";
        m_selectEasy->setEnabled(true);
        m_selectHard->setEnabled(true);
        m_difficultyLabel->setVisible(true);
        m_startButton->setEnabled(false);
        });

    connect(m_selectEasy, &QPushButton::clicked, this, [this]() {
        m_selectedMode = "PC-Easy";
        m_startButton->setEnabled(true);
        });

    connect(m_selectHard, &QPushButton::clicked, this, [this]() {
        m_selectedMode = "PC-Hard";
        m_startButton->setEnabled(true);
        });

    connect(m_startButton, &QPushButton::clicked, this, &StartWidget::StartGame);
}


void StartWidget::StartGame()
{
    std::unique_ptr<IOpponentDifficulty> difficulty;
    if (m_selectedMode == "PC-Easy") {
        difficulty = std::make_unique<EasyDifficulty>();
    }
    else if (m_selectedMode == "PC-Hard") {
        difficulty = std::make_unique<HardDifficulty>();
    }

    Game game("Player 1", "Player 2", std::move(difficulty));
    GameWidget* gameWidget = new GameWidget(std::move(game), 3, GetParentWindow());
    GetParentWindow()->setCentralWidget(gameWidget);
    deleteLater();
}
