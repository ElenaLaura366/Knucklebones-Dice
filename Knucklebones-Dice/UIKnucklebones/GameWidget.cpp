#include "GameWidget.h"

#include "MainWindow.h"

#include <cstdlib>
#include <QMessageBox>
#include <QTimer>


GameWidget::GameWidget(GameState&& gameStateRef, int diceAnimationSteps, MainWindow* parent)
	: BaseMainWidget(parent)
	, m_gameState(std::move(gameStateRef))
	, m_activePlayerColumn(0)
	, m_diceValue(0)
	, m_diceAnimationSteps(diceAnimationSteps)
	, m_diceRolled(false)
{
	GetParentWindow()->setWindowTitle("Knucklebones Dice");

	QBoxLayout* mainLayout = new QHBoxLayout(this);

	CreatePlayerLayout(mainLayout, 1, m_uiPlayer1Label, m_uiPlayer1Board);
	CreateMiddleLayout(mainLayout);
	CreatePlayerLayout(mainLayout, 2, m_uiPlayer2Label, m_uiPlayer2Board);

	m_uiDiceAnimationTimer = new QTimer(this);
	connect(m_uiDiceAnimationTimer, &QTimer::timeout, this, &GameWidget::StartDiceAnimation);

	UpdateUIState();
}

void GameWidget::CreatePlayerLayout(QBoxLayout* parentLayout, int playerNumber, QLabel*& outPlayerLabel, QGridLayout*& outBoardLayout)
{
	QVBoxLayout* playerLayout = new QVBoxLayout();
	parentLayout->addLayout(playerLayout);

	outPlayerLabel = new QLabel(QString("Player %1: 0").arg(playerNumber), this);
	outPlayerLabel->setAlignment(Qt::AlignCenter);
	playerLayout->addWidget(outPlayerLabel);

	outBoardLayout = CreateGameBoard();
	playerLayout->addLayout(outBoardLayout);

	CreateColumnSelectButtons(playerLayout, playerNumber);
}

void GameWidget::CreateMiddleLayout(QBoxLayout* parentLayout)
{
	QVBoxLayout* boardLayout = new QVBoxLayout();
	QHBoxLayout* hLayout = new QHBoxLayout();
	hLayout->setAlignment(Qt::AlignCenter);
	boardLayout->addLayout(hLayout);

	m_uiActivePlayerLabel = new QLabel("Active Player: Player 1", this);
	hLayout->addWidget(m_uiActivePlayerLabel);

	m_uiDiceLabel = new QLabel("🎲", this);
	m_uiDiceLabel->setAlignment(Qt::AlignCenter);
	m_uiDiceLabel->setStyleSheet("font-size: 48px;");
	boardLayout->addWidget(m_uiDiceLabel);

	m_uiRollDiceButton = new QPushButton("Roll Dice", this);
	connect(m_uiRollDiceButton, &QPushButton::clicked, this, &GameWidget::HandleRollDice);

	m_uiMakeMoveButton = new QPushButton("Make Move", this);
	connect(m_uiMakeMoveButton, &QPushButton::clicked, this, &GameWidget::HandleMakeMove);

	boardLayout->addWidget(m_uiRollDiceButton);
	boardLayout->addWidget(m_uiMakeMoveButton);

	parentLayout->addLayout(boardLayout);
}

QGridLayout* GameWidget::CreateGameBoard()
{
	QGridLayout* boardLayout = new QGridLayout();

	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			QLabel* cell = new QLabel("0", this);
			cell->setAlignment(Qt::AlignCenter);
			cell->setStyleSheet("background: white; border-radius: 10px;");
			boardLayout->addWidget(cell, row, col);
		}
	}
	return boardLayout;
}

void GameWidget::CreateColumnSelectButtons(QBoxLayout* playerLayout, int player)
{
	static const QString columnButtonName = "Column %1";

	QBoxLayout* buttonLayout = new QHBoxLayout();
	playerLayout->addLayout(buttonLayout);

	for (int col = 0; col < 3; ++col)
	{
		QPushButton* colButton = new QPushButton(columnButtonName.arg(col + 1), this);

		connect(colButton, &QPushButton::clicked, this, [=]() { SelectColumn(col); });

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

void GameWidget::SelectColumn(int col)
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

void GameWidget::HandleRollDice()
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

void GameWidget::DisplayGameOverMessage()
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
	close();
}

void GameWidget::HandleMakeMove()
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

	RefreshBoardUI();
	UpdateUIState();

	m_diceValue = 0;
	m_diceRolled = false;
	m_gameState.CheckForGameOver();

	if (!m_gameState.IsGameActive())
	{
		DisplayGameOverMessage();
		return;
	}
	m_gameState.NextPlayer();
	UpdateUIState();
}

void GameWidget::RefreshBoardUI()
{
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			QLabel* cell = qobject_cast<QLabel*>(m_uiPlayer1Board->itemAtPosition(row, col)->widget());
			cell->setText(QString::number(m_gameState.GetPlayer1Board().GetBoard()[row][col]));
		}
	}
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			QLabel* cell = qobject_cast<QLabel*>(m_uiPlayer2Board->itemAtPosition(row, col)->widget());
			cell->setText(QString::number(m_gameState.GetPlayer2Board().GetBoard()[row][col]));
		}
	}
}

void GameWidget::UpdateBoardUI(int player, int column, int value)
{
	QGridLayout* currentBoard = (player == 1) ? m_uiPlayer1Board : m_uiPlayer2Board;

	for (int row = 2; row >= 0; --row)
	{
		QLabel* cell = qobject_cast<QLabel*>(currentBoard->itemAtPosition(row, column)->widget());
		if (cell->text() == "0")
		{
			cell->setText(QString::number(value));
			break;
		}
	}
}

void GameWidget::UpdateUIState()
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

void GameWidget::StartDiceAnimation()
{
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
}
