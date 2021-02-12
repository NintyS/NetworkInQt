#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    client.connectToHost("localhost", 50153);

    receiveLanguages();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveLanguages() {

    client.write(QString("languages").toUtf8().toBase64());
    client.waitForBytesWritten(1000);

    client.waitForReadyRead(100);

    QString answer = QByteArray::fromBase64(client.readAll());

    qDebug() << answer;

    int c = 0;

    QString lang;

    while(c < answer.length()) {
        if(answer[c] == " ") {
            languages.push_back(lang);
            qDebug() << lang;
            lang.clear();
        } else { lang += answer[c]; }
        ++c;
    }

    c = 0;

    for(QString a : languages) {
        qDebug() << a;
        ui->comboBox->addItem(a);
        ui->comboBox_2->addItem(a);
        ++c;
    }

}

void MainWindow::addNewWord() {

    client.connectToHost("localhost", 50153);

    client.write(QString("downloadwords").toUtf8().toBase64());
    client.waitForBytesWritten(1000);

    client.waitForReadyRead(100);

    qDebug() << "1";

    QString answer;

    for(;;){
        if(answer != "ok") {
            answer = QByteArray::fromBase64(client.readAll());
            qDebug() << "2";
        } else { break; }
    }

    qDebug() << answer;

    if(answer == "ok") {
        qDebug() << "3";
        QString message = "word";
        client.write(message.toUtf8().toBase64());
        client.flush();
        client.waitForBytesWritten(1000);

        qDebug() << "4";
        client.waitForReadyRead(100);
        answer = QByteArray::fromBase64(client.readAll());
        ui->plainTextEdit_2->document()->setPlainText(answer);
        qDebug() << answer;
        qDebug() << "5";
    }
}

void MainWindow::addNewLanguage() {

    client.connectToHost("localhost", 50153);

    client.write(QString("addlanguage").toUtf8().toBase64());
    client.waitForBytesWritten(1000);

    client.waitForReadyRead(100);

    QString answer;

    for(;;){
        if(answer != "ok") {
            answer = QByteArray::fromBase64(client.readAll());
        } else { break; }
    }

    qDebug() << answer;

    if(answer == "ok") {
        QString message = ui->plainTextEdit_3->toPlainText();
        client.write(message.toUtf8().toBase64());
        client.flush();
        client.waitForBytesWritten(1000);
    }

}

void MainWindow::on_pushButton_3_clicked() {

    client.connectToHost("localhost", 50153);

    client.write(QString("translate").toUtf8().toBase64());
    client.waitForBytesWritten(1000);

    client.waitForReadyRead(100);

    QString answer;

    for(;;){
        if(answer != "ok") {
            answer = QByteArray::fromBase64(client.readAll());
        } else { break; }
    }

    qDebug() << answer;

    if(answer == "ok") {
        QString message = ui->plainTextEdit->toPlainText() + "," + ui->comboBox->currentText() + "," + ui->comboBox_2->currentText();
        client.write(message.toUtf8().toBase64());
        client.flush();
        client.waitForBytesWritten(1000);
    }

    client.waitForReadyRead(100);

    answer = QByteArray::fromBase64(client.readAll());

    ui->textEdit->setText(answer);

}

void MainWindow::on_pushButton_5_clicked()
{
    addNewLanguage();
    ui->stackedWidget->setCurrentIndex(0);
    ui->plainTextEdit_3->clear();
}

void MainWindow::on_pushButton_2_clicked()
{
    addNewWord();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_4_clicked()
{

    client.connectToHost("localhost", 50153);

    client.write(QString("addwords").toUtf8().toBase64());
    client.waitForBytesWritten(1000);

    client.waitForReadyRead(100);

    QString answer;

    for(;;){
        if(answer != "ok") {
            answer = QByteArray::fromBase64(client.readAll());
        } else { break; }
    }

    qDebug() << answer;

    if(answer == "ok") {
        QString message = ui->plainTextEdit_2->toPlainText();
        client.write(message.toUtf8().toBase64());
        client.flush();
        client.waitForBytesWritten(1000);
    }

    ui->stackedWidget->setCurrentIndex(0);
    ui->plainTextEdit_2->clear();
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
