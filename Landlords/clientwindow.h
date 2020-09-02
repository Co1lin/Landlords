#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <mytools.h>

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

    void clickConnectButton();

private slots:
    void on_pushButton_clicked();
    void displayError(QAbstractSocket::SocketError);
    void readyRead();
    void receivePackage(DataPackage data);

private:
    Ui::ClientWindow *ui;

    QTcpSocket* clientSocket;
    MyTools myTool;

};

#endif // CLIENTWINDOW_H
