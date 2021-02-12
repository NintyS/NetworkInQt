#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include <QFile>

std::vector<QString> words;

int x = 0;

void loadFromFile() {

    words.clear();

    x = 0;

    QFile languageFile(QCoreApplication::applicationDirPath() + "/languages.txt");

    qDebug() << QCoreApplication::applicationDirPath()  + "/languages.txt";

    QString name = "";

    bool howMany = true;

    if(!languageFile.exists()){
        qDebug() << "Don't exist";
    }

    if(languageFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&languageFile);
        while (!in.atEnd()) {
            QString line = in.read(1);

            if(line == ",") {
                words.push_back(name);
                name.clear();
                if(howMany) {
                    ++x;
                }
            } else if (line == "\n") {
                howMany = false;
            } else { name += line; }
        }
    } else { qDebug() << "Nosz kurwa!"; }

    languageFile.close();

}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QTcpServer server;
    if (!server.listen(QHostAddress::AnyIPv4, 50153))
        return 1;
    QObject::connect(&server, &QTcpServer::newConnection,
                         &server, [&server]() {
        QTcpSocket *socket = server.nextPendingConnection();
        qDebug() << "client connected from" << socket->peerAddress() << ":" << socket->peerPort();

        socket->waitForReadyRead(100);

        QString choose = QByteArray::fromBase64(socket->readAll());

        qDebug() << choose;

        if(choose == "languages") {
            loadFromFile();
            QString test;
            for(int i = 0; i < x; ++i) {
                test += words[i].toUtf8() + " ";
                qDebug() << test;
            }
            socket->write(test.toUtf8().toBase64());
            socket->flush();
            socket->waitForBytesWritten(3000);
        } else if (choose == "translate") {
            socket->write(QString("ok").toUtf8().toBase64());
            socket->flush();
            socket->waitForBytesWritten(3000);

            socket->waitForReadyRead(1000);
            QString answer = QByteArray::fromBase64(socket->readAll());

            qDebug() << answer;

            QString answerToTranslate;

            for(QChar a: answer) {
                if(a == ",") {
                    break;
                } else { answerToTranslate += a; }
            }

            QString lang[2];

            int u = 0;

            for(QChar a: answer) {

                if(a == ",") {
                    ++u;
                } else {
                    if(u == 1) {
                         lang[0] += a;
                    }

                    if(u == 2) {
                         lang[1] += a;
                    }
                }
            }

            QStringList answerlist = answerToTranslate.split(" ");
            qDebug() << answerlist;
            int y = 0;
            int ziemniak = 0;
            int pyra[2];
            int frytki = 0;

            std::vector<int> wordsPositions;

            for(auto a: words) {
                ++y;
                for(int i = 0; i < answerlist.size(); ++i) {
                    if((a == answerlist.at(i))&&(y > x)) {

                        qDebug() << y;

                        wordsPositions.push_back(y-1);

                        for(auto o: words) {

                            ++ziemniak;
                            if(ziemniak < x+1 ) {
                                if(o == lang[0]) {
                                    pyra[0] = ziemniak-1;
                                }

                                if(o == lang[1]) {
                                    pyra[1] = ziemniak-1;
                                }
                            }

                        }

                    }
                }
            }

            frytki = pyra[1] - pyra[0];

            qDebug() << frytki;

            QString batat;

            for(int kartofel : wordsPositions) {
                qDebug() << wordsPositions;
                batat += words[kartofel + frytki] + " ";
            }

            socket->write(batat.toUtf8().toBase64());
            socket->flush();
            socket->waitForBytesWritten(3000);

        } else if (choose == "downloadwords") {
            qDebug() << "addword - jest tru ";
            socket->write(QString("ok").toUtf8().toBase64());
            socket->flush();
            socket->waitForBytesWritten(3000);

            socket->waitForReadyRead(1000);
            QString answer = QByteArray::fromBase64(socket->readAll());

            qDebug() << answer;

            if(answer == "word") {

                QString langText;

                QFile languageFile(QCoreApplication::applicationDirPath() + "/languages.txt");
                if(languageFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
                    QTextStream in(&languageFile);
                    while (!in.atEnd()) {
                        QString line = in.read(1);
                        langText += line;
                    }

                }

                qDebug() << langText;

                socket->write(langText.toUtf8().toBase64());
                socket->flush();
                socket->waitForBytesWritten(3000);
            }

        } else if (choose == "addwords") {
            socket->write(QString("ok").toUtf8().toBase64());
            socket->flush();
            socket->waitForBytesWritten(3000);

            socket->waitForReadyRead(1000);
            QString answer = QByteArray::fromBase64(socket->readAll());

            qDebug() << answer;

            QFile languageFile(QCoreApplication::applicationDirPath() + "/languages.txt");

            languageFile.resize(0);

            if(languageFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
                languageFile.resize(0);

                QTextStream in(&languageFile);

                in << answer;

            }

            languageFile.close();

            loadFromFile();

        } else if (choose == "addlanguage") {
            socket->write(QString("ok").toUtf8().toBase64());
            socket->flush();
            socket->waitForBytesWritten(3000);

            socket->waitForReadyRead(1000);
            QString answer = QByteArray::fromBase64(socket->readAll());

            QFile languageFile(QCoreApplication::applicationDirPath() + "/languages.txt");

            bool languages = true;

            QString langText;

            if(languageFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
                QTextStream in(&languageFile);
                while (!in.atEnd()) {
                    QString line = in.read(1);
                    if((line == "\n")&&(languages)) {
                        languages = false;
                        langText += answer + ",\n";
                    } else { langText += line; }
                }

                languageFile.resize(0);
                in << langText;

            }

            languageFile.close();

            loadFromFile();

            qDebug() << answer;
        } else {
            qDebug() << "Not";
        }
        choose.clear();
        socket->close();
    });

        return app.exec();
}
