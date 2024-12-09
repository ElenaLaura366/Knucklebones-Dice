#include "StartWindow.h"

#include <QtWidgets/QApplication>
#include <QFontDatabase>


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	int fontId = QFontDatabase::addApplicationFont(":/fonts/at01.ttf");
	if (fontId == -1)
	{
		QApplication::setFont(QFont("Comic Sans MS"));
	}
	else
	{
		QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
		QFont customFont(fontFamily, 20);
		QApplication::setFont(customFont);
	}

	StartWindow mainWindow(GameState("Player 1", "Player 2"));
	mainWindow.show();

	return app.exec();
}
