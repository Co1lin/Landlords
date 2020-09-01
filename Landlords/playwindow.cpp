#include "playwindow.h"
#include "ui_playwindow.h"

#include <QDebug>
#include "mytools.h"

PlayWindow::PlayWindow(QWidget *parent, const int _id, QTcpSocket* _socket) :
    QMainWindow(parent),
    ui(new Ui::PlayWindow),
    id(_id),
    playSocket(_socket)
{
    ui->setupUi(this);
    qDebug() << "PlayWindow: " << id;
    thisTrun = false;
    ui->yesPushButton->setEnabled(false);
    ui->noPushButton->setEnabled(false);
    DataPackage confirmReady(id);
    confirmReady.type = 0;
    myTool.send(playSocket, confirmReady);
    myTool.send(playSocket, confirmReady);
}

PlayWindow::~PlayWindow()
{
    delete ui;
}
