#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

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

private:
    Ui::PlayWindow *ui;

    MyTools myTool;
    int id;
    QTcpSocket* playSocket;
    bool thisTrun;
};

#endif // PLAYWINDOW_H
