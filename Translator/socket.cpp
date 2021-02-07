#include "socket.hpp"

Socket::Socket(QObject *parent) : QObject(parent)
{

}

void Socket::Connect() {
    socket = new QTcpSocket(this);

    socket->connectToHost("192.168.0.87", 50153);

    if(socket->waitForConnected(300)){
        printf("Yes");
        socket->close();
    } else { printf("No"); }

}
