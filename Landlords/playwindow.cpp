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
    ui->myCardsGraphicsView->setScene(&myCardsGraphicsScene);
    ui->myCardsGraphicsView->show();
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
        data.sortCards();
        foreach (auto& card, data.cards)
        {
            qDebug() << card.name();
        }
        myCards = std::move(data.cards);
        showCards();
    }
}

void PlayWindow::showCards()
{
    int i = 0;
    foreach(auto& card, myCards)
    {
        auto cardItem = CardItem::map[card.name()];
        myCardsGraphicsScene.addItem(cardItem);
        cardItem->setPos(i * 60, 0);
        i++;
    }
}

void PlayWindow::fitView()
{
    auto rect = myCardsGraphicsScene.sceneRect();
    auto delta = rect.height() / 10;
    rect.setHeight(rect.height() + delta);
    ui->myCardsGraphicsView->fitInView(rect, Qt::KeepAspectRatio);
}
