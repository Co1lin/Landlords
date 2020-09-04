#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <mytools.h>

namespace Ui {
class PlayWindow;
}

class PlayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayWindow(QWidget *parent = nullptr, const int _id = 0, QTcpSocket* _socket = nullptr, const bool _firstMusic = 0);
    ~PlayWindow();

private slots:
    void readyRead();
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
    bool firstMusic;
    QMediaPlaylist playlist;
    QMediaPlayer player;


    MyTools myTool;
    int id;
    QTcpSocket* playSocket;
    QList<Card> myCards;
    QList<Card> selectedCards;
    QList<CardItem*> selectedCardItems;
    DataPackage tmpData;

    void enableChoice();
    void disableChoice();
    void addBlock();
    void showPlayersInfo(const DataPackage& data, const int _id = -1);
    void showTableCards(const DataPackage& data);
    bool beat(const QList<Card>& _lastCards = {});
    QString cardsType(const QList<Card>& cards);
    void playMusic();
};

#endif // PLAYWINDOW_H
