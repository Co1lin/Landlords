#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

private:
    Ui::ClientWindow *ui;
};

#endif // CLIENTWINDOW_H
