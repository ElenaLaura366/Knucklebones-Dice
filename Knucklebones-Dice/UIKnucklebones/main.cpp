#include "UIKnucklebones.h"

#include <QtWidgets/QApplication>


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	GameState gameState("Player 1", "Player 2");

	UIKnucklebones mainWindow(std::move(gameState));
	mainWindow.show();

	return app.exec();
}
