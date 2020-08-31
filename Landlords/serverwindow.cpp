#include "serverwindow.h"
#include "ui_serverwindow.h"

#include "playwindow.h"

ServerWindow::ServerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);

    server = new QTcpServer();
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::on_pushButton_clicked()
{
    server->close();
    if (!server->listen(QHostAddress::AnyIPv4, 6666))
    {
        qDebug() << server->errorString();
        return;
    }
    connect(server, &QTcpServer::newConnection, this, &ServerWindow::acceptConnection);
}

void ServerWindow::acceptConnection()
{
    qDebug() << "accepted";
    sockets.push_back(server->nextPendingConnection());
    ui->listWidget->addItem(sockets.last()->peerAddress().toString() + ": " + QString::number(sockets.last()->peerPort()));
//    connect(sockets.last(), &QTcpSocket::readyRead, this, [=]
//    {
//        qDebug() << "server readyread";
//    });
    if (sockets.size() == 2)
    {
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_13);
        // stream << "Start game!";
        int id = 1;
        int tmp;
        foreach (auto* socket, sockets)
        {
            data.append(QString::number(id));
            //socket->write(QByteArray::number(id));
            socket->write(data);
            connect(socket, &QTcpSocket::disconnected, [=]
            {
                qDebug() << id << " disconnected";
            });
            data.clear();
            id++;
        }
        qDebug() << "written";
        id = 0;
        auto play = new PlayWindow(nullptr, id);
        play->setWindowTitle("Server & Player " + QString::number(id));
        play->show();
        this->close();
    }
}
