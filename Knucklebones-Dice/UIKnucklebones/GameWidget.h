#pragma once

#include "BaseMainWidget.h"
#include "GameState.h"

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>


class GameWidget : public BaseMainWidget
{
	Q_OBJECT

public:
	GameWidget(GameState&& gameState, int diceAnimationSteps, MainWindow* parent);

	void DisplayGameOverMessage();

private slots:
	void HandleRollDice();
	void HandleMakeMove();
	void SelectColumn(int col);

private:
	void CreatePlayerLayout(QBoxLayout* mainLayout, int player, QLabel*& outPlayerLabel, QGridLayout*& outBoardLayout);
	void CreateMiddleLayout(QBoxLayout* parentLayout);
	QGridLayout* CreateGameBoard();
	void CreateColumnSelectButtons(QBoxLayout* playerLayout, int player);
	void UpdateBoardUI(int player, int column, int value);
	void UpdateUIState();
	void RefreshBoardUI();
	void StartDiceAnimation();

private:
	QGridLayout* m_uiPlayer1Board;
	QGridLayout* m_uiPlayer2Board;
	QLabel* m_uiPlayer1Label;
	QLabel* m_uiPlayer2Label;
	QLabel* m_uiActivePlayerLabel;
	QPushButton* m_uiRollDiceButton;
	QPushButton* m_uiMakeMoveButton;
	QLabel* m_uiDiceLabel;
	QTimer* m_uiDiceAnimationTimer;
	std::vector<QPushButton*> m_uiPlayer1ColumnButtons;
	std::vector<QPushButton*> m_uiPlayer2ColumnButtons;

private:
	GameState m_gameState;

	int m_activePlayerColumn;
	int m_diceValue;
	int m_animationSteps;
	int m_diceAnimationSteps;
	bool m_diceRolled;
};
