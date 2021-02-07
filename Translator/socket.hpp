#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <QTcpSocket>
#include <QObject>

class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = nullptr);

    void Connect();

signals:

private:
    QTcpSocket *socket;

};

#endif // SOCKET_HPP
