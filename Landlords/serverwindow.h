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
    void haveMessageToRead(QTcpSocket* socket, const int id);
    void receivePackage(DataPackage data);

private:
    Ui::ServerWindow *ui;

    QTcpServer* serverSocket;
    QVector<QTcpSocket*> sockets;
    int confirmed;
    //quint64 bytesToRead;
    MyTools myTool;
};

#endif // SERVERWINDOW_H
