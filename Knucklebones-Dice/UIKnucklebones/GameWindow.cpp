#include "GameWindow.h"

#include <cstdlib>
#include <QMessageBox>


GameWindow::GameWindow(GameState&& gameStateRef, int diceAnimationSteps, QWidget* parent)
	: QMainWindow(parent)
	, m_gameState(std::move(gameStateRef))
	, m_activePlayerColumn(0)
	, m_diceValue(0)
	, m_diceAnimationSteps(diceAnimationSteps)
	, m_diceRolled(false)
{
	setWindowTitle("Knucklebones Dice");
	resize(800, 600);

	QWidget* centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);

	QBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

	createPlayerLayout(mainLayout, 1, m_uiPlayer1Label, m_uiPlayer1Board);
	createMiddleLayout(mainLayout);
	createPlayerLayout(mainLayout, 2, m_uiPlayer2Label, m_uiPlayer2Board);

	m_uiDiceAnimationTimer = new QTimer(this);
	connect(m_uiDiceAnimationTimer, &QTimer::timeout, this, [=]() {
		int randomValue = std::rand() % 6 + 1;
		m_uiDiceLabel->setText(QString("🎲 %1").arg(randomValue));

		if (++m_animationSteps >= m_diceAnimationSteps) {
			m_uiDiceAnimationTimer->stop();
			m_diceValue = rand() % 6 + 1;
			m_uiDiceLabel->setText(QString("🎲 %1").arg(m_diceValue));
			m_uiActivePlayerLabel->setText(QString("Active Player: %1 - Rolled Dice: %2")
				.arg(m_gameState.GetActivePlayer().GetName().data())
				.arg(m_diceValue));
			m_diceRolled = true;
		}
		});

	updateUIState();
}

void GameWindow::closeEvent(QCloseEvent* event)
{
	QApplication::quit();
	event->accept();
}

void GameWindow::createPlayerLayout(QBoxLayout* parentLayout, int playerNumber, QLabel*& outPlayerLabel, QGridLayout*& outBoardLayout)
{
	QVBoxLayout* playerLayout = new QVBoxLayout();
	parentLayout->addLayout(playerLayout);

	outPlayerLabel = new QLabel(QString("Player %1: 0").arg(playerNumber), this);
	outPlayerLabel->setAlignment(Qt::AlignCenter);
	playerLayout->addWidget(outPlayerLabel);

	outBoardLayout = createGameBoard();
	playerLayout->addLayout(outBoardLayout);

	createColumnSelectButtons(playerLayout, playerNumber);
}

void GameWindow::createMiddleLayout(QBoxLayout* parentLayout)
{
	QBoxLayout* boardLayout = new QVBoxLayout();
	m_uiActivePlayerLabel = new QLabel("Active Player: Player 1", this);
	boardLayout->addWidget(m_uiActivePlayerLabel);

	m_uiDiceLabel = new QLabel("🎲", this);
	m_uiDiceLabel->setAlignment(Qt::AlignCenter);
	m_uiDiceLabel->setStyleSheet("font-size: 48px;");
	boardLayout->addWidget(m_uiDiceLabel);

	m_uiRollDiceButton = new QPushButton("Roll Dice", this);
	connect(m_uiRollDiceButton, &QPushButton::clicked, this, &GameWindow::handleRollDice);

	m_uiMakeMoveButton = new QPushButton("Make Move", this);
	connect(m_uiMakeMoveButton, &QPushButton::clicked, this, &GameWindow::handleMakeMove);

	boardLayout->addWidget(m_uiRollDiceButton);
	boardLayout->addWidget(m_uiMakeMoveButton);

	parentLayout->addLayout(boardLayout);
}

QGridLayout* GameWindow::createGameBoard()
{
	QGridLayout* boardLayout = new QGridLayout();

	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			QPushButton* cellButton = new QPushButton(this);
			cellButton->setFixedSize(50, 50);
			cellButton->setText("0");
			boardLayout->addWidget(cellButton, row, col);
		}
	}
	return boardLayout;
}

void GameWindow::createColumnSelectButtons(QBoxLayout* playerLayout, int player)
{
	static const QString columnButtonName = "Column %1";

	QBoxLayout* buttonLayout = new QHBoxLayout();
	playerLayout->addLayout(buttonLayout);

	for (int col = 0; col < 3; ++col)
	{
		QPushButton* colButton = new QPushButton(columnButtonName.arg(col + 1), this);
		colButton->setFixedSize(80, 30);

		connect(colButton, &QPushButton::clicked, this, [=]() { selectColumn(col); });

		buttonLayout->addWidget(colButton);

		if (player == 1)
		{
			m_uiPlayer1ColumnButtons.push_back(colButton);
		}
		else
		{
			m_uiPlayer2ColumnButtons.push_back(colButton);
		}
	}
}

void GameWindow::selectColumn(int col)
{
	m_activePlayerColumn = col;

	if (m_gameState.GetActiveBoard().IsColumnFull(m_activePlayerColumn))
	{
		m_uiActivePlayerLabel->setText("Selected column is full! Choose another column.");
		return;
	}

	m_uiActivePlayerLabel->setText(QString("Active Player: %1 - Column %2 Selected")
		.arg(m_gameState.GetActivePlayer().GetName().data())
		.arg(col + 1));
}

void GameWindow::handleRollDice()
{
	if (!m_gameState.IsGameActive())
	{
		m_uiActivePlayerLabel->setText("Game is over!");
		return;
	}

	if (m_diceRolled)
	{
		m_uiActivePlayerLabel->setText("You have already rolled the dice! Make your move.");
		return;
	}

	m_animationSteps = 0;
	m_uiDiceAnimationTimer->start(100);
	m_uiActivePlayerLabel->setText("Rolling the dice...");
}

void GameWindow::displayGameOverMessage()
{
	int player1Score = m_gameState.GetPlayer1().GetScore();
	int player2Score = m_gameState.GetPlayer2().GetScore();

	QString winnerMessage;
	if (player1Score > player2Score)
	{
		winnerMessage = "Game Over! Player 1 wins!";
	}
	else if (player2Score > player1Score)
	{
		winnerMessage = "Game Over! Player 2 wins!";
	}
	else
	{
		winnerMessage = "Game Over! It's a draw!";
	}

	QMessageBox::information(this, "Game Over", winnerMessage);
	QApplication::quit();
}

void GameWindow::handleMakeMove()
{
	if (!m_diceRolled)
	{
		m_uiActivePlayerLabel->setText("Roll the dice first!");
		return;
	}

	Board& activeBoard = m_gameState.GetActiveBoard();
	if (activeBoard.IsColumnFull(m_activePlayerColumn))
	{
		m_uiActivePlayerLabel->setText("Column is full! Choose another column.");
		return;
	}

	activeBoard.MakeMove(m_activePlayerColumn, m_diceValue);
	m_gameState.CancelMatchingDiceOnOpponentBoard(m_activePlayerColumn, m_diceValue);
	m_gameState.UpdateScores();

	refreshBoardUI();
	updateUIState();

	m_diceValue = 0;
	m_diceRolled = false;
	m_gameState.CheckForGameOver();

	if (!m_gameState.IsGameActive())
	{
		displayGameOverMessage();
		return;
	}
	m_gameState.NextPlayer();
	updateUIState();
}

void GameWindow::refreshBoardUI()
{
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			QPushButton* cell = qobject_cast<QPushButton*>(m_uiPlayer1Board->itemAtPosition(row, col)->widget());
			cell->setText(QString::number(m_gameState.GetPlayer1Board().GetBoard()[row][col]));
		}
	}
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			QPushButton* cell = qobject_cast<QPushButton*>(m_uiPlayer2Board->itemAtPosition(row, col)->widget());
			cell->setText(QString::number(m_gameState.GetPlayer2Board().GetBoard()[row][col]));
		}
	}
}

void GameWindow::updateBoardUI(int player, int column, int value)
{
	QGridLayout* currentBoard = (player == 1) ? m_uiPlayer1Board : m_uiPlayer2Board;

	for (int row = 2; row >= 0; --row)
	{
		QPushButton* cell = qobject_cast<QPushButton*>(currentBoard->itemAtPosition(row, column)->widget());
		if (cell->text() == "0")
		{
			cell->setText(QString::number(value));
			break;
		}
	}
}

void GameWindow::updateUIState()
{
	m_uiPlayer1Label->setText(QString("Player 1: %1").arg(m_gameState.GetPlayer1().GetScore()));
	m_uiPlayer2Label->setText(QString("Player 2: %1").arg(m_gameState.GetPlayer2().GetScore()));
	m_uiActivePlayerLabel->setText(QString("Active Player: %1")
		.arg(m_gameState.GetActivePlayer().GetName().data()));

	bool isPlayer1Turn = (&m_gameState.GetActivePlayer() == &m_gameState.GetPlayer1());

	for (auto button : m_uiPlayer1ColumnButtons)
	{
		button->setEnabled(isPlayer1Turn);
	}
	for (auto button : m_uiPlayer2ColumnButtons)
	{
		button->setEnabled(!isPlayer1Turn);
	}
}
