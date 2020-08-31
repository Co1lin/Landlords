#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>

namespace Ui {
class ServerWindow;
}

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

private:
    Ui::ServerWindow *ui;
};

#endif // SERVERWINDOW_H
