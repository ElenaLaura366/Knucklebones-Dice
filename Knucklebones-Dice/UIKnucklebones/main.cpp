#include "UIKnucklebones.h"

#include <QtWidgets/QApplication>


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Board player1Board, player2Board;
	GameState gameState;

	Player player1("Player 1");
	Player player2("Player 2");

	gameState.AddPlayer(player1);
	gameState.AddPlayer(player2);

	UIKnucklebones mainWindow(gameState, player1, player2);
	mainWindow.show();

	return app.exec();
}
