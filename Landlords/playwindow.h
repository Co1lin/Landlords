#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
//#include <QTimer>
#include <mytools.h>

namespace Ui {
class PlayWindow;
}

class PlayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayWindow(QWidget *parent = nullptr, const int _id = 0, QTcpSocket* _socket = nullptr);
    ~PlayWindow();

private slots:
    void receivePackage(DataPackage data);
    void showCards();
    void fitView();

    void on_yesPushButton_clicked();

    void on_noPushButton_clicked();

private:
    Ui::PlayWindow *ui;

    QGraphicsScene myCardsGraphicsScene;
    QGraphicsScene bottomCardsGraphicsScene;
    QGraphicsScene tableGraphicsScene;
    QVector<QGraphicsScene*> playersInfoScene;
    QGraphicsRectItem* block;
    QTimer fitTimer;

    MyTools myTool;
    int id;
    QTcpSocket* playSocket;
    QList<Card> myCards;
    QList<Card> selectedCards;
    QList<CardItem*> selectedCardItems;
    DataPackage tmpData;

    bool thisTrun;

    void enableChoice();
    void disableChoice();
    void addBlock();
    void showPlayersInfo(const DataPackage& data, const int _id = -1);
    void showTableCards(const DataPackage& data);
    bool beat(const QList<Card>& _lastCards = {});
};

#endif // PLAYWINDOW_H
