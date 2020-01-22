#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <QFile>

int startApp(QApplication * a) {
    MainWindow w;

    a->setStyle(QStyleFactory::create("Fusion"));

    w.show();
    return a->exec();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    a.setStyle(QStyleFactory::create("Fusion"));

    w.show();
    return a.exec();
}
