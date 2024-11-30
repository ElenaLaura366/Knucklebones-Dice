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
#include <memory>
#include "GameState.h"
#include "Board.h"
#include "Player.h"

class UIGameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit UIGameWindow(QWidget* parent = nullptr);
    ~UIGameWindow() = default;

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

    std::shared_ptr<Board> board;
    std::shared_ptr<GameState> gameState;
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;

    int activePlayerColumn;
    int diceValue;
	bool diceRolled;
    int animationSteps;
    const int maxAnimationSteps = 20;
};
