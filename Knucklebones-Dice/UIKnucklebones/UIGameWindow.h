#pragma once

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
#include "GameState.h"
#include "Board.h"
#include "Player.h"

class UIGameWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit UIGameWindow(GameState& gameState, Player& player1, Player& player2, QWidget* parent = nullptr);
    ~UIGameWindow() = default;

    void displayGameOverMessage();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void handleRollDice();
    void handleMakeMove();
    void selectColumn(int col);

private:
    QGridLayout* createGameBoard();
    void createColumnButtons(QVBoxLayout* playerLayout, int player);
    void updateBoardUI(int player, int column, int value);
    void updateUIState();

    QGridLayout* player1Board;
    QGridLayout* player2Board;
    QLabel* player1Label;
    QLabel* player2Label;
    QLabel* activePlayerLabel;
    QPushButton* rollDiceButton;
    QPushButton* makeMoveButton;
    QLabel* diceLabel;
    QTimer* diceAnimationTimer;

    std::vector<QPushButton*> player1ColumnButtons;
    std::vector<QPushButton*> player2ColumnButtons;

    GameState& gameState;
    Player& player1;
    Player& player2;

    int activePlayerColumn;
    int diceValue;
    bool diceRolled;
    int animationSteps;
    const int maxAnimationSteps = 20;
};
