#include "UIKnucklebones.h"
#include <QtWidgets/QApplication>
#include <QDebug>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    UIKnucklebones w;
    w.show();
    QObject::connect(&a, &QApplication::aboutToQuit, []() {
        qDebug() << "Object tree before exit:";
        QCoreApplication::instance()->dumpObjectTree();
        });
    return a.exec();
}