#include "UIKnucklebones.h"
#include <QtWidgets/QApplication>
#include <QDebug>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);
    UIKnucklebones w;
    w.show();
    return a.exec();
}