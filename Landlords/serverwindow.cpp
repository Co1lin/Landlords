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
    static int receivedMsg = 0;
    if (data.type == 0)
    {
        qDebug() << "confirmed: " << ++confirmed << data.id;
        if (confirmed == 6)
        {
            qDebug() << "all players has been ready!";
            // deal 17*3 cards
            // QVector<Card> cardVector;
            QVector<QChar> cardPattern = { 'C', 'D', 'H', 'S' };
            foreach (auto& pattern, cardPattern)
            {
                for (int i = 3; i <= 15; i++)
                {
                    Card tmp(pattern, i);
                    cardVector.push_back(tmp);
                }
            }
            Card tmp1('K', 16);
            cardVector.push_back(tmp1);
            Card tmp2('K', 17);
            cardVector.push_back(tmp2);
            auto seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(cardVector.begin(), cardVector.end(), std::default_random_engine(static_cast<unsigned>(seed)));
            for (int id = 0; id < 3; id++)
                playerInfo.push_back(PlayerInfo(id, 17, "?"));
            DataPackage dealCard[3];
            for (int id = 0; id < 3; id++)
            {
                dealCard[id].type = 1;  // deal cards
//                for (int j = 0; j < 3; j++)
//                    dealCard[id].playerInfos[j] = PlayerInfo(j, 17, "?");
                dealCard[id].playerInfo = playerInfo;
                for (int i = 0; i < 17; i++)
                    dealCard[id].cards.push_back(cardVector[i + 17 * id]);
            }
            for (int id = 0; id < 3; id++)
                myTool.send(sockets[id], dealCard[id]);
        }
    }
    else if (data.type == 1)
    {
        receivedMsg++;
        if (receivedMsg == 3)
        {
            // decide the landlord
            qDebug() << "start to decide the landlord";
            int randomPlayer = QRandomGenerator::global()->bounded(3);
            DataPackage dataToSend;
            dataToSend.type = 3;
            dataToSend.msg << "landlord?";
            myTool.send(sockets[randomPlayer], dataToSend);
            receivedMsg = 0;
        }
    }
    else if (data.type == 3)
    {
        decideLandlord(data);
    }
    else if (data.type == 2)    // received a player's played cards
    {
        playerInfo[data.id].cardsRemain -= data.cards.size();   // update the player's info
        DataPackage dataToSend;
        dataToSend.type = 2;
        dataToSend.msg << "wait";
        if (data.msg[0] == "pass")
        {
            dataToSend.cards = cardToBeat;
            if (MyTools::nextId(data.id) == playerToBeat)
                cardToBeat = dataToSend.cards = {};
        }
        else
        {
            cardToBeat = dataToSend.cards = data.cards;
            playerToBeat = data.id;
        }
        dataToSend.playerInfo = playerInfo;
        myTool.send(sockets[data.id], dataToSend);
        myTool.send(sockets[MyTools::nextId(data.id + 1)], dataToSend);
        dataToSend.msg[0] = "your turn";
        myTool.send(sockets[MyTools::nextId(data.id)], dataToSend);
    }
}

void ServerWindow::decideLandlord(DataPackage data)
{
    static int landlord = -1;
    static QVector<int> phase;
    phase.push_back(data.id);
    bool flag = false;
    if (data.msg[0] == "yes")
    {
        landlord = data.id;
        if (phase.size() == 3)  // can be decided
        {
            qDebug() << "decide the landlord: " << landlord;
            flag = true;
        }
        else
        {
            DataPackage dataToSend;
            dataToSend.type = 3;
            dataToSend.msg << "landlord??";
            myTool.send(sockets[MyTools::nextId(data.id)], dataToSend);
        }
    }
    else
    {
        if (phase.size() == 3)  // can be decided
        {
            landlord = landlord == -1 ? phase[0] : landlord;
            qDebug() << "decide the landlord: " << landlord;
            flag = true;
        }
        else
        {
            DataPackage dataToSend;
            dataToSend.type = 3;
            if (landlord == -1)
                dataToSend.msg << "landlord?";
            else
                dataToSend.msg << "landlord??";
            myTool.send(sockets[MyTools::nextId(data.id)], dataToSend);
        }
    }
    if (flag)
    {
        // boardcast the landlord and send the last 3 cards
        QList<Card> cardsAtBottom;
        for (auto iter = cardVector.rbegin(); iter != cardVector.rbegin() + 3; iter++)
        {
            cardsAtBottom << *iter;
        }
        MyTools::sortCards(cardsAtBottom);
        DataPackage decision;
        decision.type = 3;
        decision.msg << "have landlord";
        decision.cards = cardsAtBottom;
        for (int id = 0; id <= 2; id++)
        {
            if (id == landlord)
            {
                playerInfo[landlord].role = "地主";
                playerInfo[landlord].cardsRemain += 3;
            }
            else
                playerInfo[id].role = "农民";
        }
        decision.playerInfo = playerInfo;
        for (int id = 0; id < 3; id++)
            myTool.send(sockets[id], decision);
    }
}



//void ServerWindow::readyRead()
//{
//    myTool.read(clientSocket);
//}
