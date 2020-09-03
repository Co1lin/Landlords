#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>

#include <QtNetwork>
#include <mytools.h>

namespace Ui {
class ServerWindow;
}

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

signals:


private slots:
    void acceptConnection();
    void on_pushButton_clicked();
    void receivePackage(DataPackage data);

private:
    Ui::ServerWindow *ui;

    QTcpServer* serverSocket;
    QVector<QTcpSocket*> sockets;
    //int confirmed;
    MyTools myTool;
    QVector<Card> cardVector;
    QVector<PlayerInfo> playerInfo;
    QList<Card> cardToBeat;
    int playerToBeat;

    void decideLandlord(DataPackage data);
};

#endif // SERVERWINDOW_H
