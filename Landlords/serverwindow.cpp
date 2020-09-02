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
    // myself->clickConnectButton();    // need to run after complete debugging!
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
        DataPackage sendId;
        sendId.id = 0;
        foreach (auto* socket, sockets)
        {
            connect(socket, &QTcpSocket::readyRead, this, [=]{ myTool.read(socket); });
            myTool.send(socket, sendId);
            sendId.id++;
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
        {
            qDebug() << "all players has been ready!";
            // deal 17*3 cards
            QVector<Card> cardVector;
            QVector<QChar> cardPattern = { 'C', 'D', 'H', 'S' };
            foreach (auto& pattern, cardPattern)
            {
                for (int i = 3; i <= 15; i++)
                {
                    Card tmp(pattern, i);
                    cardVector.push_back(tmp);
                    CardItem::map[tmp.name()] = new CardItem(tmp);
                }
            }
            Card tmp1('K', 16);
            cardVector.push_back(tmp1);
            CardItem::map[tmp1.name()] = new CardItem(tmp1);
            Card tmp2('K', 17);
            cardVector.push_back(tmp2);
            CardItem::map[tmp2.name()] = new CardItem(tmp2);
            auto seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(cardVector.begin(), cardVector.end(), std::default_random_engine(static_cast<unsigned>(seed)));
            DataPackage dealCard[3];
            for (int id = 0; id < 3; id++)
            {
                dealCard[id].type = 1;  // deal cards
                for (int i = 0; i < 17; i++)
                    dealCard[id].cards.push_back(cardVector[i + 17 * id]);
                myTool.send(sockets[id], dealCard[id]);
            }
        }
    }
}

//void ServerWindow::readyRead()
//{
//    myTool.read(clientSocket);
//}
