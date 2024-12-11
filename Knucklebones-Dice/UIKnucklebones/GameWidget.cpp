#include "GameWidget.h"

#include "MainWindow.h"

#include <cstdlib>
#include <QMessageBox>
#include <QTimer>
#include <QApplication>


GameWidget::GameWidget(Game&& game, int diceAnimationSteps, MainWindow* parent)
	: BaseMainWidget(parent)
	, m_game(std::move(game))
	, m_activePlayerColumn(-1)
	, m_diceValue(0)
	, m_diceAnimationSteps(diceAnimationSteps)
	, m_diceRolled(false)
{
	GetParentWindow()->setWindowTitle("Knucklebones Dice");

	m_uiDefaultCellStyle = QString(R"(
		border: 1px solid black;
		background-color: rgba(255, 255, 255, 200);
		color: black;
		font-size: %1px;
	)").arg(3 * GetParentWindow()->font().pointSize());

	m_uiHighlightedCellStyle = QString(R"(
		border: 1px solid black;
		background-color: rgba(0, 0, 255, 200);
		color: white;
		font-size: %1px;
	)").arg(3 * GetParentWindow()->font().pointSize());

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

	QHBoxLayout* diceLayout = new QHBoxLayout();
	diceLayout->setAlignment(Qt::AlignCenter);
	boardLayout->addLayout(diceLayout);

	QLabel* diceLabel = new QLabel("🎲", this);
	diceLabel->setAlignment(Qt::AlignCenter);
	diceLabel->setStyleSheet(QString("font-size: %1px;").arg(4 * GetParentWindow()->font().pointSize()));
	diceLayout->addWidget(diceLabel);

	m_uiDiceNumberLabel = new QLabel(" ", this);
	m_uiDiceNumberLabel->setAlignment(Qt::AlignCenter);
	m_uiDiceNumberLabel->setStyleSheet(QString("font-size: %1px;").arg(4 * GetParentWindow()->font().pointSize()));
	m_uiDiceNumberLabel->setMinimumWidth(6 * GetParentWindow()->font().pointSize());
	diceLayout->addWidget(m_uiDiceNumberLabel);

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
			cell->setStyleSheet(m_uiDefaultCellStyle);
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

	if (m_game.GetActiveBoard().IsColumnFull(m_activePlayerColumn))
	{
		m_uiActivePlayerLabel->setText("Selected column is full! Choose another column.");
		return;
	}

	QGridLayout* activeBoardLayout = IsPlayer1Turn() ? m_uiPlayer1Board : m_uiPlayer2Board;
	for (int row = 0; row < 3; ++row)
	{
		for (int j = 0; j < 3; ++j)
		{
			QLabel* cell = qobject_cast<QLabel*>(activeBoardLayout->itemAtPosition(row, j)->widget());
			cell->setStyleSheet(j == col ? m_uiHighlightedCellStyle : m_uiDefaultCellStyle);
		}
	}

	m_uiActivePlayerLabel->setText(QString("Active Player: %1 - Column %2 Selected")
		.arg(m_game.GetActivePlayer().GetName().data())
		.arg(col + 1));
}

void GameWidget::HandleRollDice()
{
	if (!m_game.IsGameActive())
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
	int player1Score = m_game.GetPlayer1().GetScore();
	int player2Score = m_game.GetPlayer2().GetScore();

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

	if (m_activePlayerColumn == -1)
	{
		m_uiActivePlayerLabel->setText("Select a column first!");
		return;
	}

	Board& activeBoard = m_game.GetActiveBoard();
	if (activeBoard.IsColumnFull(m_activePlayerColumn))
	{
		m_uiActivePlayerLabel->setText("Column is full! Choose another column.");
		return;
	}

	activeBoard.MakeMove(m_activePlayerColumn, m_diceValue);
	m_game.CancelMatchingDiceOnOpponentBoard(m_activePlayerColumn, m_diceValue);
	m_game.UpdateScores();

	RefreshBoardUI();
	UpdateUIState();

	m_diceValue = 0;
	m_diceRolled = false;
	m_game.CheckForGameOver();

	if (!m_game.IsGameActive())
	{
		DisplayGameOverMessage();
		return;
	}
	m_game.NextPlayer();
	UpdateUIState();
}

void GameWidget::RefreshBoardUI()
{
	m_activePlayerColumn = -1;

	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			QLabel* cell = qobject_cast<QLabel*>(m_uiPlayer1Board->itemAtPosition(row, col)->widget());
			cell->setText(QString::number(m_game.GetPlayer1Board()[row][col]));
		}
	}
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			QLabel* cell = qobject_cast<QLabel*>(m_uiPlayer2Board->itemAtPosition(row, col)->widget());
			cell->setText(QString::number(m_game.GetPlayer2Board()[row][col]));
		}
	}
}

void GameWidget::UpdateUIState()
{
	m_uiPlayer1Label->setText(QString("Player 1: %1").arg(m_game.GetPlayer1().GetScore()));
	m_uiPlayer2Label->setText(QString("Player 2: %1").arg(m_game.GetPlayer2().GetScore()));
	m_uiActivePlayerLabel->setText(QString("Active Player: %1")
		.arg(m_game.GetActivePlayer().GetName().data()));

	const bool isPlayer1Turn = IsPlayer1Turn();
	for (auto button : m_uiPlayer1ColumnButtons)
	{
		button->setEnabled(isPlayer1Turn);
	}
	for (auto button : m_uiPlayer2ColumnButtons)
	{
		button->setEnabled(!isPlayer1Turn);
	}

	QGridLayout* opponentPlayerBoard = isPlayer1Turn ? m_uiPlayer2Board : m_uiPlayer1Board;
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			QLabel* cell = qobject_cast<QLabel*>(opponentPlayerBoard->itemAtPosition(row, col)->widget());
			cell->setStyleSheet(m_uiDefaultCellStyle);
		}
	}
}

void GameWidget::StartDiceAnimation()
{
	int randomValue = std::rand() % 6 + 1;
	m_uiDiceNumberLabel->setText(QString::number(randomValue));

	if (++m_animationSteps >= m_diceAnimationSteps) {
		m_uiDiceAnimationTimer->stop();
		m_diceValue = rand() % 6 + 1;
		m_uiDiceNumberLabel->setText(QString::number(m_diceValue));
		m_uiActivePlayerLabel->setText(QString("Active Player: %1 - Rolled Dice: %2")
			.arg(m_game.GetActivePlayer().GetName().data())
			.arg(m_diceValue));
		m_diceRolled = true;
	}
}

bool GameWidget::IsPlayer1Turn() const
{
	return (&m_game.GetActivePlayer() == &m_game.GetPlayer1());
}
