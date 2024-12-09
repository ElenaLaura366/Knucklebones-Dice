#pragma once

#include "GameState.h"
#include "Board.h"
#include "Player.h"

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QApplication>
#include <QTimer>
#include <vector>


class UIGameWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit UIGameWindow(GameState&& gameState, int diceAnimationSteps, QWidget* parent = nullptr);
	~UIGameWindow() = default;

	void displayGameOverMessage();

protected:
	void closeEvent(QCloseEvent* event) override;

private slots:
	void handleRollDice();
	void handleMakeMove();
	void selectColumn(int col);

private:
	void createPlayerLayout(QBoxLayout* mainLayout, int player, QLabel*& outPlayerLabel, QGridLayout*& outBoardLayout);
	void createMiddleLayout(QBoxLayout* parentLayout);
	QGridLayout* createGameBoard();
	void createColumnSelectButtons(QBoxLayout* playerLayout, int player);
	void updateBoardUI(int player, int column, int value);
	void updateUIState();
	void refreshBoardUI();

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

	GameState m_gameState;

	int m_activePlayerColumn;
	int m_diceValue;
	int m_animationSteps;
	int m_diceAnimationSteps;
	bool m_diceRolled;
};
