#include "GameWidget.h"

#include "MainWindow.h"

#include <cstdlib>
#include <QMessageBox>
#include <QTimer>
#include <QApplication>


GameWidget::GameWidget(Game&& game, int diceAnimationSteps, MainWindow* parent)
	: BaseMainWidget(parent)
	, m_game(std::move(game))
	, m_activeColumn(-1)
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

	m_uiHighlightCellStyle = QString(R"(
		border: 1px solid black;
		background-color: rgba(0, 0, 255, 200);
		color: white;
		font-size: %1px;
	)").arg(3 * GetParentWindow()->font().pointSize());

	m_uiLowHighlightCellStyle = QString(R"(
		border: 1px solid black;
		background-color: rgba(0, 150, 200, 200);
		color: white;
		font-size: %1px;
	)").arg(3 * GetParentWindow()->font().pointSize());

	QBoxLayout* mainLayout = new QHBoxLayout(this);

	CreatePlayerLayout(mainLayout, 1, m_uiLabel1, m_uiBoard1);
	CreateMiddleLayout(mainLayout);
	CreatePlayerLayout(mainLayout, 2, m_uiLabel2, m_uiBoard2);

	m_uiDiceAnimationTimer = new QTimer(this);
	connect(m_uiDiceAnimationTimer, &QTimer::timeout, this, &GameWidget::StartDiceAnimation);

	RefreshUI();
}

void GameWidget::CreatePlayerLayout(QBoxLayout* parentLayout, int playerNumber, QLabel*& outPlayerLabel, QGridLayout*& outBoardLayout)
{
	QVBoxLayout* playerLayout = new QVBoxLayout(this);
	parentLayout->addLayout(playerLayout);

	outPlayerLabel = new QLabel(QString("Player %1: 0").arg(playerNumber), this);
	outPlayerLabel->setAlignment(Qt::AlignCenter);
	playerLayout->addWidget(outPlayerLabel);

	outBoardLayout = CreateBoardLayout();
	playerLayout->addLayout(outBoardLayout);

	CreateColumnSelectButtons(playerLayout, playerNumber);
}

void GameWidget::CreateMiddleLayout(QBoxLayout* parentLayout)
{
	QVBoxLayout* boardLayout = new QVBoxLayout(this);
	QHBoxLayout* hLayout = new QHBoxLayout(this);
	hLayout->setAlignment(Qt::AlignCenter);
	boardLayout->addLayout(hLayout);

	m_uiInfoLabel = new QLabel("Active Player: Player 1", this);
	hLayout->addWidget(m_uiInfoLabel);

	QHBoxLayout* diceLayout = new QHBoxLayout(this);
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

QGridLayout* GameWidget::CreateBoardLayout()
{
	QGridLayout* boardLayout = new QGridLayout(this);

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

	QBoxLayout* buttonLayout = new QHBoxLayout(this);
	playerLayout->addLayout(buttonLayout);

	for (int col = 0; col < 3; ++col)
	{
		QPushButton* colButton = new QPushButton(columnButtonName.arg(col + 1), this);

		connect(colButton, &QPushButton::clicked, this, [=]() { SelectColumn(col); });

		buttonLayout->addWidget(colButton);

		if (player == 1)
		{
			m_uiColumnButtons1.push_back(colButton);
		}
		else
		{
			m_uiColumnButtons2.push_back(colButton);
		}
	}
}

void GameWidget::SelectColumn(int col)
{
	if (m_activeColumn == col)
	{
		HandleMakeMove();
		return;
	}

	if (std::as_const(m_game).GetActiveBoard().IsColumnFull(col))
	{
		m_uiInfoLabel->setText("Selected column is full! Choose another column.");
		return;
	}

	m_activeColumn = col;

	QGridLayout* activeBoardLayout = IsPlayer1Turn() ? m_uiBoard1 : m_uiBoard2;
	RefreshUI();

	m_uiInfoLabel->setText(QString("Active Player: %1 - Column %2 Selected")
		.arg(std::as_const(m_game).GetActivePlayer().GetName().data())
		.arg(col + 1));
}

void GameWidget::HandleRollDice()
{
	if (m_game.IsGameOver())
	{
		m_uiInfoLabel->setText("Game is over!");
		return;
	}

	if (m_diceRolled)
	{
		m_uiInfoLabel->setText("You have already rolled the dice! Make your move.");
		return;
	}

	m_animationSteps = 0;
	m_uiDiceAnimationTimer->start(100);
	m_uiInfoLabel->setText("Rolling the dice...");
}

void GameWidget::HandleMakeMove()
{
	if (!m_diceRolled)
	{
		m_uiInfoLabel->setText("Roll the dice first!");
		return;
	}

	if (m_activeColumn == -1)
	{
		m_uiInfoLabel->setText("Select a column first!");
		return;
	}

	const Board& activeBoard = std::as_const(m_game).GetActiveBoard();
	if (activeBoard.IsColumnFull(m_activeColumn))
	{
		m_uiInfoLabel->setText("Column is full! Choose another column.");
		return;
	}

	m_game.MakeMove(m_activeColumn, m_diceValue);

	m_activeColumn = -1;
	RefreshUI();

	m_diceValue = 0;
	m_diceRolled = false;

	if (m_game.IsGameOver())
	{
		DisplayGameOverMessage();
		QApplication::quit();
	}
}

void GameWidget::DisplayGameOverMessage()
{
	int player1Score = m_game.CalculateScore(1);
	int player2Score = m_game.CalculateScore(2);

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
}

void GameWidget::RefreshUI()
{
	m_uiLabel1->setText(QString("Player 1: %1").arg(m_game.CalculateScore(1)));
	m_uiLabel2->setText(QString("Player 2: %1").arg(m_game.CalculateScore(2)));
	m_uiInfoLabel->setText(QString("Active Player: %1")
		.arg(std::as_const(m_game).GetActivePlayer().GetName().data()));

	const bool isPlayer1Turn = IsPlayer1Turn();
	for (auto button : m_uiColumnButtons1)
	{
		button->setEnabled(isPlayer1Turn);
	}
	for (auto button : m_uiColumnButtons2)
	{
		button->setEnabled(!isPlayer1Turn);
	}

	const auto refreshCellNumbers = [](const Board& board, QGridLayout* boardLayout) {
		for (int row = 0; row < 3; ++row)
		{
			for (int col = 0; col < 3; ++col)
			{
				QLabel* cell = qobject_cast<QLabel*>(boardLayout->itemAtPosition(row, col)->widget());
				cell->setText(QString::number(board[row][col]));
			}
		}
	};
	refreshCellNumbers(m_game.GetBoard1(), m_uiBoard1);
	refreshCellNumbers(m_game.GetBoard2(), m_uiBoard2);


	const auto refreshBoardCellStyles = [this](QGridLayout* board, bool isActive) {
		for (int row = 0; row < 3; ++row)
		{
			for (int col = 0; col < 3; ++col)
			{
				QLabel* cell = qobject_cast<QLabel*>(board->itemAtPosition(row, col)->widget());
				if (isActive && m_activeColumn == col)
				{
					cell->setStyleSheet(m_uiHighlightCellStyle);
				}
				else if (!isActive && m_activeColumn == col)
				{
					cell->setStyleSheet(m_uiLowHighlightCellStyle);
				}
				else
				{
					cell->setStyleSheet(m_uiDefaultCellStyle);
				}
			}
		}
		};
	refreshBoardCellStyles(m_uiBoard1, IsPlayer1Turn());
	refreshBoardCellStyles(m_uiBoard2, !IsPlayer1Turn());
}

void GameWidget::StartDiceAnimation()
{
	int randomValue = std::rand() % 6 + 1;
	m_uiDiceNumberLabel->setText(QString::number(randomValue));

	if (++m_animationSteps >= m_diceAnimationSteps) {
		m_uiDiceAnimationTimer->stop();
		m_diceValue = rand() % 6 + 1;
		m_uiDiceNumberLabel->setText(QString::number(m_diceValue));
		m_uiInfoLabel->setText(QString("Active Player: %1 - Rolled Dice: %2")
			.arg(std::as_const(m_game).GetActivePlayer().GetName().data())
			.arg(m_diceValue));
		m_diceRolled = true;
	}
}

bool GameWidget::IsPlayer1Turn() const
{
	return (&m_game.GetActivePlayer() == &m_game.GetPlayer1());
}
