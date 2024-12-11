#include "MainWindow.h"
#include <QFile>
#include <QApplication>
#include <QFontDatabase>
#include <QIcon>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QDebug>
#include <qmessagebox.h>

static void SetApplicationFont(QApplication& app)
{
	int fontId = QFontDatabase::addApplicationFont(":/fonts/SpenbebGame-R9q46.otf");
	if (fontId == -1)
	{
		app.setFont(QFont("Comic Sans MS"));
	}
	else
	{
		QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
		QFont customFont(fontFamily, 14);
		app.setFont(customFont);
	}
}

static void LoadApplicationStyle(QApplication& app)
{
	QFile styleFile(":/themes/spongebob_theme.qss");
	if (styleFile.open(QFile::ReadOnly))
	{
		QString theme = styleFile.readAll();
		app.setStyleSheet(theme);
	}
}

static void StartBackgroundMusic(QMediaPlayer& player, QAudioOutput& audioOutput)
{
	player.setAudioOutput(&audioOutput);
	player.setSource(QUrl("qrc:/soundtracks/spongebobSong.wav"));
	player.setLoops(QMediaPlayer::Infinite);
	player.play();
	audioOutput.setVolume(0.005f);

	if (player.source().isEmpty())
	{
		qDebug() << "Failed to load audio file";
	}
	else
	{
		qDebug() << "Audio file loaded correctly";
	}

	// sa ne atentioneze daca apare o eroare la redare
	QObject::connect(&player, &QMediaPlayer::errorOccurred, [](QMediaPlayer::Error error) {
		QMessageBox::critical(nullptr, "Audio error", QString("Audio error: %1").arg(error));
		});
}

int main(int argc, char* argv[])
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	QApplication app(argc, argv);

	app.setWindowIcon(QIcon(":/images/icon.png"));

	SetApplicationFont(app);
	LoadApplicationStyle(app);

	QMediaPlayer player;
	QAudioOutput audioOutput;
	StartBackgroundMusic(player, audioOutput);

	MainWindow mainWindow(Game("Player 1", "Player 2"));
	mainWindow.show();

	return app.exec();
}
