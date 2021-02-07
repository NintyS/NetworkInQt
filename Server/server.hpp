#ifndef SERVER_HPP
#define SERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>

class server : public QObject
{
    Q_OBJECT
public:
    explicit server(QObject *parent = nullptr);

signals:

public slots:
    void newConnection();

private:
    QTcpServer *serverObject;

};

#endif // SERVER_HPP
