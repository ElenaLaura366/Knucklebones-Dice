#pragma once

#include "BaseMainWidget.h"
#include "Game.h"

#include <QPushButton>
#include <QLabel>
#include <QMainWindow>


namespace ui
{
	/*!
	*	\brief Widget that allows the user to select the game mode and difficulty.
	*/
	class StartWidget : public BaseMainWidget
	{
		Q_OBJECT

	public:
		StartWidget(MainWindow* parent);

	protected slots:
		/*!
		*	\brief Slot that sets the game mode to multiplayer.It does that by creating a new `ui::GameWidget`
		*	and attaching it to the parent `ui::MainWindow`.
		*/
		void StartGame();

	protected:
		/*!
		*	\brief Enum representing the game mode currenty chosen.
		*/
		enum class GameMode
		{
			None,			/*!< No game mode selected */
			Multiplayer,	/*!< Multiplayer mode selected */
			PC_Easy,		/*!< Play vs PC on easy mode */
			PC_Hard			/*!< Play vs PC on hard mode */
		};

	private:
		QPushButton* m_startButton;
		QPushButton* m_selectMultiplayer;
		QPushButton* m_selectPC;
		QPushButton* m_selectEasy;
		QPushButton* m_selectHard;

		QLabel* m_difficultyLabel;
		GameMode m_gameMode;
	};
}
