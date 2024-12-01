#pragma once

#include <QtWidgets>
#include <QPushButton>
#include <QCloseEvent>
#include <QApplication>
#include <QMainWindow>
#include "UIGameWindow.h"
#include "GameState.h"
#include "Player.h"

class UIKnucklebones : public QMainWindow {
    Q_OBJECT

public:
    UIKnucklebones(GameState& gameState, Player& player1, Player& player2, QWidget* parent = nullptr);
    ~UIKnucklebones();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void startGame();

private:
    QPushButton* startButton;
    UIGameWindow* uigameWindow;
    GameState& m_gameState;
    Player& m_player1;
    Player& m_player2;
};