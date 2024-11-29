#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QCloseEvent>
#include "ui_UIKnucklebones.h"
#include "UIGameWindow.h"

class UIKnucklebones : public QMainWindow
{
    Q_OBJECT

public:
    UIKnucklebones(QWidget* parent = nullptr);
    ~UIKnucklebones();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void startGame();

private:
    QPushButton* startButton;
    UIGameWindow* uigameWindow;
    Ui::UIKnucklebonesClass ui;
};
