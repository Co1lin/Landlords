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
    // UI
    qDebug() << "PlayWindow: " << id;
    thisTrun = false;
    ui->yesPushButton->setEnabled(false);
    ui->noPushButton->setEnabled(false);
    myTool.installMyEventFilter(&bottomCardsGraphicsScene);
    myTool.installMyEventFilter(&tableGraphicsScene);
    ui->myCardsGraphicsView->setScene(&myCardsGraphicsScene);
    ui->bottomCardsGraphicsView->setScene(&bottomCardsGraphicsScene);
    ui->tableGraphicsView->setScene(&tableGraphicsScene);
    for (int i = 0; i <= 2; i++)
        playersInfoScene.push_back(new QGraphicsScene());
    ui->player0GraphicsView->setScene(playersInfoScene[id]);
    ui->player1GraphicsView->setScene(playersInfoScene[MyTools::nextId(id)]);
    ui->player2GraphicsView->setScene(playersInfoScene[MyTools::nextId(MyTools::nextId(id))]);
    ui->myCardsGraphicsView->show();
    ui->bottomCardsGraphicsView->show();
    ui->tableGraphicsView->show();
    ui->player0GraphicsView->show();
    ui->player1GraphicsView->show();
    ui->player2GraphicsView->show();
    connect(&fitTimer, &QTimer::timeout, this, &PlayWindow::fitView);
    fitTimer.start(33);

    // network
    DataPackage confirmReady(id);
    confirmReady.type = 0;
    myTool.send(playSocket, confirmReady);
    // sticky package test
    myTool.send(playSocket, confirmReady);
    connect(playSocket, &QTcpSocket::readyRead, this, [=]
    {
        myTool.read(playSocket);
    });
    connect(&myTool, &MyTools::transferPackage, this, &PlayWindow::receivePackage);
}

PlayWindow::~PlayWindow()
{
    delete ui;
}

void PlayWindow::receivePackage(DataPackage data)
{
    qDebug() << "id: " << id;
    if (data.type == 1) // receive dealed 17 cards
    {
        // data.sortCards();
        foreach (auto& card, data.cards)
        {
            qDebug() << card.name();
        }
        myCards = std::move(data.cards);
        showCards();
        showPlayersInfo(data);
        DataPackage dataToSend(id);
        dataToSend.type = 1;
        myTool.send(playSocket, dataToSend);
    }
    else if (data.type == 3)    // decide the landlord
    {
        if (data.msg[0] == "landlord?")
        {
            qDebug() << "叫地主？";
            ui->noticeLabel->setText("叫地主？");
            enableChoice();
        }
        else if (data.msg[0] == "landlord??")
        {
            ui->noticeLabel->setText("抢地主？");
            enableChoice();
        }
        else if (data.msg[0] == "have landlord")    // have decide the landlord
        {
            showPlayersInfo(data);
            // show the bottom cards
            int i = 0;
            foreach (auto& card, data.cards)
            {
                auto cardItem = new CardItem(card);
                // bottomCardsGraphicsScene.clear();
                bottomCardsGraphicsScene.addItem(cardItem);
                cardItem->setPos(i * 100, 0);
                i++;
            }
            if (data.playerInfo[id].role == "地主")  // I am the landlords!
            {
                // add three cards
                myCards << data.cards;
                std::sort(myCards.begin(), myCards.end(), std::greater<Card>());
                showCards();
                // play cards first
                ui->noticeLabel->setText("请出牌");
                ui->yesPushButton->setEnabled(true);
            }
        }
    }
    else if (data.type == 2)    // playing game
    {
        showPlayersInfo(data);
        showTableCards(data);
        if (data.msg[0] == "wait")
        {
            // nothing
        }
        else if (data.msg[0] == "your turn")
        {
            enableChoice();
            ui->noticeLabel->setText("请出牌");
            tmpData = data;
        }
    }
}

void PlayWindow::showCards()
{
    myCardsGraphicsScene.clear();
    addBlock();
    MyTools::sortCards(myCards);
    int i = 0;
    foreach(auto& card, myCards)
    {
        auto cardItem = new CardItem(card);
        myCardsGraphicsScene.addItem(cardItem);
        cardItem->setPos(i * 60, 55);
        i++;
    }
}

void PlayWindow::showPlayersInfo(const DataPackage& data, const int _id)
{
    if (_id == -1)
    {
        for (int i = 0; i <= 2; i++)
        {
            playersInfoScene[i]->clear();
            auto playerInfo = new PlayerInfo(data.playerInfo[i]);
            playersInfoScene[i]->addItem(playerInfo);
        }
    }
    else
    {
        playersInfoScene[id]->clear();
        auto playerInfo = new PlayerInfo(data.playerInfo[id]);
        playersInfoScene[id]->addItem(playerInfo);
    }
}

void PlayWindow::showTableCards(const DataPackage &data)
{
    tableGraphicsScene.clear();
    int i = 0;
    foreach (auto card, data.cards)
    {
        auto cardItem = new CardItem(card);
        tableGraphicsScene.addItem(cardItem);
        cardItem->setPos(i * 100, 0);
        i++;
    }
}

void PlayWindow::fitView()
{
    auto rect = myCardsGraphicsScene.sceneRect();
    auto delta = rect.height() / 10;
    rect.setHeight(rect.height() + delta);
    ui->myCardsGraphicsView->fitInView(rect, Qt::KeepAspectRatio);

    ui->bottomCardsGraphicsView->fitInView(bottomCardsGraphicsScene.sceneRect(), Qt::KeepAspectRatio);

    rect = tableGraphicsScene.sceneRect();
    delta = rect.height() / 5;
    rect.setHeight(rect.height() + delta);
    ui->tableGraphicsView->fitInView(rect, Qt::KeepAspectRatio);

    ui->player0GraphicsView->fitInView(playersInfoScene[id]->sceneRect(), Qt::KeepAspectRatio);
    ui->player1GraphicsView->fitInView(playersInfoScene[MyTools::nextId(id)]->sceneRect(), Qt::KeepAspectRatio);
    ui->player2GraphicsView->fitInView(playersInfoScene[MyTools::nextId(MyTools::nextId(id))]->sceneRect(), Qt::KeepAspectRatio);
}

void PlayWindow::addBlock()
{
    block = new QGraphicsRectItem(0, 0, 17 * 60, 50);
    myCardsGraphicsScene.addItem(block);
    block->setPen(QPen(Qt::yellow));
    block->setPos(0, 0);
}

void PlayWindow::enableChoice()
{
    ui->yesPushButton->setEnabled(true);
    ui->noPushButton->setEnabled(true);
}

void PlayWindow::disableChoice()
{
    ui->yesPushButton->setEnabled(false);
    ui->noPushButton->setEnabled(false);
}

void PlayWindow::on_yesPushButton_clicked()
{
    if (ui->noticeLabel->text() == "叫地主？" ||
        ui->noticeLabel->text() == "抢地主？")
    {
        DataPackage dataToSend(id);
        dataToSend.type = 3;
        dataToSend.msg << "yes";
        myTool.send(playSocket, dataToSend);
    }
    else if (ui->noticeLabel->text() == "请出牌")
    {
        if (beat(tmpData.cards))
        {
            DataPackage dataToSend(id);
            dataToSend.type = 2;
            dataToSend.msg << "play";
            dataToSend.cards = selectedCards;
            myTool.send(playSocket, dataToSend);
            // delete the cards that the player played
            foreach (auto item, selectedCardItems)
            {
                int index = myCards.indexOf(item->getCard());
                myCards.erase(myCards.begin() + index);
                myCardsGraphicsScene.removeItem(item);
            }
            // update the view of my cards
            showCards();
        }
        else
        {
            ui->noticeLabel->text() = "出牌不符合规则！";
            return;
        }
    }
    ui->noticeLabel->setText("等待");
    disableChoice();
}

void PlayWindow::on_noPushButton_clicked()
{
    if (ui->noticeLabel->text() == "叫地主？" ||
        ui->noticeLabel->text() == "抢地主？")
    {
        DataPackage dataToSend(id);
        dataToSend.type = 3;
        dataToSend.msg << "no";
        myTool.send(playSocket, dataToSend);
    }
    else if (ui->noticeLabel->text() == "请出牌")
    {
        // pass
        DataPackage dataToSend(id);
        dataToSend.type = 2;
        dataToSend.msg << "pass";
        myTool.send(playSocket, dataToSend);
    }
    ui->noticeLabel->setText("等待");
    disableChoice();
}

bool PlayWindow::beat(const QList<Card>& _lastCards)
{
    // get all cards selected
    selectedCards.clear();
    selectedCardItems.clear();
    auto cardItems = myCardsGraphicsScene.items();
    foreach (QGraphicsItem* item, cardItems)
    {
        auto cardItem = dynamic_cast<CardItem*>(item);
        if (cardItem && cardItem->isSelected())
        {
            selectedCards << cardItem->getCard();
            selectedCardItems << cardItem;
        }
    }
    if (selectedCards.empty())
        return false;
    else if (_lastCards.size() == 0 || cardItems.size() == 20 + 1)
        return true;
    else
    {
        // judgement
        qDebug() << "judgement";
        return true;
    }
}
