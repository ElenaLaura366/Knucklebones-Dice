#include "MainWindow.h"
#include <QFile>
#include <QApplication>
#include <QFontDatabase>
#include <QIcon>


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/images/icon.png"));

	int fontId = QFontDatabase::addApplicationFont(":/fonts/SpenbebGame-R9q46.otf");
	if (fontId == -1) {
		QApplication::setFont(QFont("Comic Sans MS"));
	}
	else {
		QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
		QFont customFont(fontFamily, 14);
		QApplication::setFont(customFont);
	}

	QFile styleFile(":/themes/spongebob_theme.qss");
	if (styleFile.open(QFile::ReadOnly)) {
		QString theme = styleFile.readAll();
		app.setStyleSheet(theme);
	}

	MainWindow mainWindow(GameState("Player 1", "Player 2"));
	mainWindow.show();

	return app.exec();
}
