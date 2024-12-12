#pragma once

#include "BaseMainWidget.h"
#include "Game.h"

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>


class GameWidget : public BaseMainWidget
{
	Q_OBJECT

public:
	GameWidget(Game&& game, int diceAnimationSteps, MainWindow* parent);

private slots:
	void SelectColumn(int col);
	void HandleRollDice();
	void HandleMakeMove();

private:
	void CreatePlayerLayout(QBoxLayout* mainLayout, int player, QLabel*& outPlayerLabel, QGridLayout*& outBoardLayout);
	void CreateMiddleLayout(QBoxLayout* parentLayout);
	QGridLayout* CreateBoardLayout();
	void CreateColumnSelectButtons(QBoxLayout* playerLayout, int player);

	void DisplayGameOverMessage();
	void UpdateUIState();
	void RefreshBoardUI();
	void StartDiceAnimation();
	bool IsPlayer1Turn() const;

	void SetBoardStyles(QGridLayout* boardLayout, bool isActive);

private:
	QGridLayout* m_uiPlayer1Board;
	QGridLayout* m_uiPlayer2Board;
	QLabel* m_uiPlayer1Label;
	QLabel* m_uiPlayer2Label;
	QLabel* m_uiActivePlayerLabel;
	QPushButton* m_uiRollDiceButton;
	QPushButton* m_uiMakeMoveButton;
	QLabel* m_uiDiceNumberLabel;
	QTimer* m_uiDiceAnimationTimer;
	std::vector<QPushButton*> m_uiPlayer1ColumnButtons;
	std::vector<QPushButton*> m_uiPlayer2ColumnButtons;

	QString m_uiDefaultCellStyle;
	QString m_uiHighlightedCellStyle;

private:
	Game m_game;

	int m_activePlayerColumn;
	int m_diceValue;
	int m_animationSteps;
	int m_diceAnimationSteps;
	bool m_diceRolled;
};
