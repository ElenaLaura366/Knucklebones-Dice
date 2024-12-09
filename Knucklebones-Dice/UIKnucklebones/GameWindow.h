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


class GameWindow : public QMainWindow
{
	Q_OBJECT

public:
	GameWindow(GameState&& gameState, int diceAnimationSteps, QWidget* parent = nullptr);
	~GameWindow() = default;

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

private:
	QGridLayout* m_uiPlayer1Board = nullptr;
	QGridLayout* m_uiPlayer2Board = nullptr;
	QLabel* m_uiPlayer1Label = nullptr;
	QLabel* m_uiPlayer2Label = nullptr;
	QLabel* m_uiActivePlayerLabel = nullptr;
	QPushButton* m_uiRollDiceButton = nullptr;
	QPushButton* m_uiMakeMoveButton = nullptr;
	QLabel* m_uiDiceLabel = nullptr;
	QTimer* m_uiDiceAnimationTimer = nullptr;

	std::vector<QPushButton*> m_uiPlayer1ColumnButtons = {};
	std::vector<QPushButton*> m_uiPlayer2ColumnButtons = {};

	GameState m_gameState;

	int m_activePlayerColumn;
	int m_diceValue;
	int m_animationSteps;
	int m_diceAnimationSteps;
	bool m_diceRolled;
};
