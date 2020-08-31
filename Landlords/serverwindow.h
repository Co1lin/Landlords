#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>

#include <QtNetwork>

namespace Ui {
class ServerWindow;
}

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

private slots:
    void acceptConnection();
    void on_pushButton_clicked();

private:
    Ui::ServerWindow *ui;

    QTcpServer* server;
    QVector<QTcpSocket*> sockets;
};

#endif // SERVERWINDOW_H
