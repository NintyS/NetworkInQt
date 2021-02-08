#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    client.connectToHost("46.41.137.178", 50153);
    connect(&client, SIGNAL(readyRead()), this, SLOT(receiveLanguages()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveLanguages() {

}

void MainWindow::receiveWords() {

}

void MainWindow::addNewWord() {

}

void MainWindow::addNewLanguage() {

}
