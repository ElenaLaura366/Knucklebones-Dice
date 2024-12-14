#pragma once

#include "BaseMainWidget.h"
#include "Game.h"

#include <QPushButton>
#include <QLabel>
#include <QMainWindow>


namespace ui
{
	class StartWidget : public BaseMainWidget
	{
		Q_OBJECT

	public:
		StartWidget(MainWindow* parent);

	private slots:
		void StartGame();

	private:
		enum class GameMode
		{
			None,
			Multiplayer,
			PC_Easy,
			PC_Hard
		};

	private:
		QPushButton* m_selectMultiplayer;
		QPushButton* m_selectPC;
		QPushButton* m_selectEasy;
		QPushButton* m_selectHard;
		QPushButton* m_startButton;

		QLabel* m_difficultyLabel;
		GameMode m_gameMode;
	};
}
