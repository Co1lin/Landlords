#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

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
    void readMessage();

private:
    Ui::ClientWindow *ui;

    QTcpSocket* clientSocket;

};

#endif // CLIENTWINDOW_H
