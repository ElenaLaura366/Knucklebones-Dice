#include "UIGameWindow.h"

#include <cstdlib>
#include <QMessageBox>


UIGameWindow::UIGameWindow(GameState&& gameStateRef, int diceAnimationSteps, QWidget* parent)
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
	QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

	QVBoxLayout* player1Layout = new QVBoxLayout();
	player1Label = new QLabel("Player 1: 0", this);
	player1Label->setAlignment(Qt::AlignCenter);
	player1Layout->addWidget(player1Label);

	player1Board = createGameBoard();
	player1Layout->addLayout(player1Board);

	createColumnButtons(player1Layout, 1);
	mainLayout->addLayout(player1Layout);

	QVBoxLayout* boardLayout = new QVBoxLayout();
	activePlayerLabel = new QLabel("Active Player: Player 1", this);
	boardLayout->addWidget(activePlayerLabel);

	diceLabel = new QLabel("🎲", this);
	diceLabel->setAlignment(Qt::AlignCenter);
	diceLabel->setStyleSheet("font-size: 48px;");
	boardLayout->addWidget(diceLabel);

	rollDiceButton = new QPushButton("Roll Dice", this);
	connect(rollDiceButton, &QPushButton::clicked, this, &UIGameWindow::handleRollDice);

	makeMoveButton = new QPushButton("Make Move", this);
	connect(makeMoveButton, &QPushButton::clicked, this, &UIGameWindow::handleMakeMove);

	boardLayout->addWidget(rollDiceButton);
	boardLayout->addWidget(makeMoveButton);

	mainLayout->addLayout(boardLayout);

	QVBoxLayout* player2Layout = new QVBoxLayout();
	player2Label = new QLabel("Player 2: 0", this);
	player2Label->setAlignment(Qt::AlignCenter);
	player2Layout->addWidget(player2Label);

	player2Board = createGameBoard();
	player2Layout->addLayout(player2Board);

	createColumnButtons(player2Layout, 2);
	mainLayout->addLayout(player2Layout);

	diceAnimationTimer = new QTimer(this);
	connect(diceAnimationTimer, &QTimer::timeout, this, [=]() {
		int randomValue = std::rand() % 6 + 1;
		diceLabel->setText(QString("🎲 %1").arg(randomValue));

		if (++m_animationSteps >= m_diceAnimationSteps) {
			diceAnimationTimer->stop();
			m_diceValue = rand() % 6 + 1;
			diceLabel->setText(QString("🎲 %1").arg(m_diceValue));
			activePlayerLabel->setText(QString("Active Player: %1 - Rolled Dice: %2")
				.arg(m_gameState.GetActivePlayer().GetName().data())
				.arg(m_diceValue));
			m_diceRolled = true;
		}
		});

	setCentralWidget(centralWidget);
	updateUIState();
}

void UIGameWindow::closeEvent(QCloseEvent* event)
{
	QApplication::quit();
	event->accept();
}

QGridLayout* UIGameWindow::createGameBoard()
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

void UIGameWindow::createColumnButtons(QVBoxLayout* playerLayout, int player)
{
	QHBoxLayout* buttonLayout = new QHBoxLayout();

	for (int col = 0; col < 3; ++col)
	{
		QPushButton* colButton = new QPushButton(QString("Column %1").arg(col + 1), this);
		colButton->setFixedSize(80, 30);

		connect(colButton, &QPushButton::clicked, this, [=]() { selectColumn(col); });

		buttonLayout->addWidget(colButton);

		if (player == 1)
			player1ColumnButtons.push_back(colButton);
		else
			player2ColumnButtons.push_back(colButton);
	}
	playerLayout->addLayout(buttonLayout);
}

void UIGameWindow::selectColumn(int col)
{
	m_activePlayerColumn = col;

	if (m_gameState.GetActiveBoard().IsColumnFull(m_activePlayerColumn))
	{
		activePlayerLabel->setText("Selected column is full! Choose another column.");
		return;
	}

	activePlayerLabel->setText(QString("Active Player: %1 - Column %2 Selected")
		.arg(m_gameState.GetActivePlayer().GetName().data())
		.arg(col + 1));
}

void UIGameWindow::handleRollDice()
{
	if (!m_gameState.IsGameActive())
	{
		activePlayerLabel->setText("Game is over!");
		return;
	}

	if (m_diceRolled)
	{
		activePlayerLabel->setText("You have already rolled the dice! Make your move.");
		return;
	}

	m_animationSteps = 0;
	diceAnimationTimer->start(100);
	activePlayerLabel->setText("Rolling the dice...");
}

void UIGameWindow::displayGameOverMessage()
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
	else {
		winnerMessage = "Game Over! It's a draw!";
	}

	QMessageBox::information(this, "Game Over", winnerMessage);
	QApplication::quit();
}

void UIGameWindow::handleMakeMove()
{
	if (!m_diceRolled)
	{
		activePlayerLabel->setText("Roll the dice first!");
		return;
	}

	Board& activeBoard = m_gameState.GetActiveBoard();
	if (activeBoard.IsColumnFull(m_activePlayerColumn))
	{
		activePlayerLabel->setText("Column is full! Choose another column.");
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

void UIGameWindow::refreshBoardUI()
{
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			QPushButton* cell = qobject_cast<QPushButton*>(player1Board->itemAtPosition(row, col)->widget());
			cell->setText(QString::number(m_gameState.GetPlayer1Board().GetBoard()[row][col]));
		}
	}
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			QPushButton* cell = qobject_cast<QPushButton*>(player2Board->itemAtPosition(row, col)->widget());
			cell->setText(QString::number(m_gameState.GetPlayer2Board().GetBoard()[row][col]));
		}
	}
}

void UIGameWindow::updateBoardUI(int player, int column, int value)
{
	QGridLayout* currentBoard = (player == 1) ? player1Board : player2Board;

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

void UIGameWindow::updateUIState()
{
	player1Label->setText(QString("Player 1: %1").arg(m_gameState.GetPlayer1().GetScore()));
	player2Label->setText(QString("Player 2: %1").arg(m_gameState.GetPlayer2().GetScore()));
	activePlayerLabel->setText(QString("Active Player: %1")
		.arg(m_gameState.GetActivePlayer().GetName().data()));

	bool isPlayer1Turn = (&m_gameState.GetActivePlayer() == &m_gameState.GetPlayer1());

	for (auto button : player1ColumnButtons)
	{
		button->setEnabled(isPlayer1Turn);
	}
	for (auto button : player2ColumnButtons)
	{
		button->setEnabled(!isPlayer1Turn);
	}
}
