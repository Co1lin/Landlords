#include "serverwindow.h"
#include "ui_serverwindow.h"

#include "playwindow.h"
#include "clientwindow.h"
#include "mytools.h"

ServerWindow::ServerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);

    serverSocket = new QTcpServer();
    ui->pushButton->click();
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::on_pushButton_clicked()
{
    serverSocket->close();
    if (!serverSocket->listen(QHostAddress::AnyIPv4, 6666))
    {
        qDebug() << serverSocket->errorString();
        return;
    }
    connect(serverSocket, &QTcpServer::newConnection, this, &ServerWindow::acceptConnection);
    confirmed = 0;
    auto myself = new ClientWindow();
    // myself->clickConnectButton();
}

void ServerWindow::acceptConnection()
{
    qDebug() << "accepted a connection";
    sockets.push_back(serverSocket->nextPendingConnection());
    ui->listWidget->addItem(sockets.last()->peerAddress().toString() + ": " + QString::number(sockets.last()->peerPort()));
    if (sockets.size() == 3)
    {
        qDebug() << "Three players are here!";
        connect(&myTool, &MyTools::transferPackage, this, &ServerWindow::receivePackage);
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_13);
        int id = 0;
        foreach (auto* socket, sockets)
        {
            stream << id;
            socket->write(data);
            connect(socket, &QTcpSocket::disconnected, [=]
            {
                qDebug() << id << " disconnected";
            });
            data.clear();
            // "new data is available for reading from the device's current read channel"
            connect(socket, &QTcpSocket::readyRead, this, [=]
            {
                haveMessageToRead(socket, id);
            });
            stream.device()->seek(0);
            id++;
        }
        qDebug() << "written";
        this->close();
    }
}

void ServerWindow::receivePackage(DataPackage data)
{
    qDebug() << "received one!";
    if (data.type == 0)
    {
        qDebug() << "confirmed: " << ++confirmed << data.id;
        if (confirmed == 6)
            qDebug() << "all players has been ready!";
    }

}

void ServerWindow::haveMessageToRead(QTcpSocket* socket, const int id)
{
//    QDataStream in(socket);
//    static qint32 bytesToRead = 0;
//    if (socket->bytesAvailable() < sizeof(qint32))
//        return;
//    while (socket->bytesAvailable())
//    {
//        if (socket->bytesAvailable() >= sizeof(qint32) && bytesToRead == 0)
//        {
//            in >> bytesToRead;
//        }
//        if (socket->bytesAvailable() >= bytesToRead && bytesToRead != 0)
//        {
//            int received = 100;
//            qDebug() << "socket->bytesAvailable()";
//            qDebug() << socket->bytesAvailable();
//            //in >> received;
//            char temp[10] = { 0 };
//            in.readRawData(temp, 4);
//            QByteArray buffer(temp, 4);
//            QDataStream stream(&buffer, QIODevice::ReadWrite);
//            stream >> received;
//            if (received < 100)
//                qDebug() << "confirmed: " << ++confirmed << received;
//            if (confirmed == 6)
//                qDebug() << "all players connected!";

//            bytesToRead = 0;
//        }
//    }
    //DataPackage receivedData(-1);
    myTool.read(socket);
//    if (receivedData.id != id)
//    {
//        qDebug() << "Error: id doesn't match!";
//        return;
//    }
//    if (receivedData.type == 0)
//    {
//        qDebug() << "confirmed: " << ++confirmed << id;
//        if (confirmed == 6)
//            qDebug() << "all players has been ready!";
//    }

}
