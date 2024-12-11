#include "MainWindow.h"
#include <QFile>
#include <QApplication>
#include <QFontDatabase>
#include <QIcon>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QDebug>
#include <qmessagebox.h>

void startBackgroundMusic(QMediaPlayer* player, QAudioOutput* audioOutput) {
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl(":/soundtracks/spongebobSong.wav"));
    player->setLoops(QMediaPlayer::Infinite);
    player->play();
    audioOutput->setVolume(1.0);

    if (player->source().isEmpty()) {
        qDebug() << "Fișierul audio nu a fost încărcat corect!";
    }
    else {
        qDebug() << "Fișierul audio a fost încărcat!";
    }
	//sa ne atentioneze daca apare o eroare la redare
    QObject::connect(player, &QMediaPlayer::errorOccurred, [](QMediaPlayer::Error error) {
        QMessageBox::critical(nullptr, "Eroare la redare", QString("Eroare la redare audio: %1").arg(error));
        });
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/images/icon.png"));

    QMediaPlayer player;
    QAudioOutput audioOutput;
    startBackgroundMusic(&player, &audioOutput);

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
