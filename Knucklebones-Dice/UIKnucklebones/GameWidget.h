#pragma once

#include "BaseMainWidget.h"
#include "Game.h"

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>


namespace ui
{
	class GameWidget : public BaseMainWidget, public game::IGameListener
	{
		Q_OBJECT

	public:
		GameWidget(game::Game&& game, int diceAnimationSteps, MainWindow* parent);
		~GameWidget();

	private slots:
		void SelectColumn(int col);
		void HandleRollDice();
		void HandleMakeMove();

	private:
		void CreatePlayerLayout(QBoxLayout* mainLayout, int player, QLabel*& outPlayerLabel, QGridLayout*& outBoardLayout);
		void CreateMiddleLayout(QBoxLayout* parentLayout);
		QGridLayout* CreateBoardLayout();
		void CreateColumnSelectButtons(QBoxLayout* playerLayout, int player);

		void DisplayGameOverMessage();
		void RefreshUI();
		void DiceAnimationStep();
		bool IsPlayer1Turn() const;
		int GetBoardRows() const;
		int GetBoardCols() const;

	private:
		void OnGameOver() override;
		void OnBoardUpdate() override;

	private:
		QGridLayout* m_uiBoard1;
		QGridLayout* m_uiBoard2;
		QLabel* m_uiLabel1;
		QLabel* m_uiLabel2;
		QLabel* m_uiInfoLabel;
		QPushButton* m_uiRollDiceButton;
		QPushButton* m_uiMakeMoveButton;
		QLabel* m_uiDiceNumberLabel;
		QTimer* m_uiDiceAnimationTimer;
		std::vector<QPushButton*> m_uiColumnButtons1;
		std::vector<QPushButton*> m_uiColumnButtons2;

	private:
		game::Game m_game;

		int m_activeColumn;
		int m_diceValue;
		int m_animationSteps;
		int m_diceAnimationSteps;
		bool m_diceRolled;
	};
}
