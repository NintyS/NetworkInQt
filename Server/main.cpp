#include <QCoreApplication>
#include "server.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    server myServer;

    return a.exec();
}
