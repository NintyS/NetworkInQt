#include "server.hpp"

server::server(QObject *parent) : QObject(parent) {
    serverObject = new QTcpServer(this);

    connect(serverObject, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(serverObject->listen(QHostAddress::Any, 50153)) {
        printf("Yes");
    } else { printf("No"); }
}

void server::newConnection() {

    printf("KuTaSu KoŹ-leńcia");

    QTcpSocket *socket = serverObject->nextPendingConnection();

    socket->write("Test\n");
    socket->flush();

    socket->waitForBytesWritten(300);

    socket->close();
}
