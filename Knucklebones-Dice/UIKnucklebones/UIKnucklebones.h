#pragma once

#include "UIGameWindow.h"
#include "GameState.h"
#include "Player.h"

#include <QtWidgets>
#include <QPushButton>
#include <QCloseEvent>
#include <QApplication>
#include <QMainWindow>


class UIKnucklebones : public QMainWindow
{
	Q_OBJECT

public:
	UIKnucklebones(GameState&& gameState, QWidget* parent = nullptr);

protected:
	void closeEvent(QCloseEvent* event) override;

private slots:
	void startGame();

private:
	QPushButton* startButton;
	std::unique_ptr<UIGameWindow> m_uiGameWindow;
	GameState m_gameState;
};
