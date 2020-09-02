#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QGraphicsScene>
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

private:
    Ui::PlayWindow *ui;

    QGraphicsScene myCardsGraphicsScene;
    QTimer fitTimer;

    MyTools myTool;
    int id;
    QTcpSocket* playSocket;
    QList<Card> myCards;
    bool thisTrun;
};

#endif // PLAYWINDOW_H
