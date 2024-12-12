#pragma once

#include "BaseMainWidget.h"
#include "Game.h"

#include <QPushButton>
#include <QLabel>
#include <QMainWindow>


class StartWidget : public BaseMainWidget
{
    Q_OBJECT

public:
    StartWidget(Game&& game, MainWindow* parent);

private slots:
    void StartGame();

private:
    QPushButton* m_selectMultiplayer;
    QPushButton* m_selectPC;
    QPushButton* m_selectEasy;
    QPushButton* m_selectHard;
    QPushButton* m_startButton;

    QLabel* m_difficultyLabel; 
    QString m_selectedMode;

private:
    Game m_game;
};
