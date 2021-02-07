#include "mainwindow.h"

#include <QApplication>

#include "socket.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Socket test;
    test.Connect();

    MainWindow w;
    w.show();
    return a.exec();
}
