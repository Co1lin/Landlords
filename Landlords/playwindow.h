#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>

namespace Ui {
class PlayWindow;
}

class PlayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayWindow(QWidget *parent = nullptr, const int _id = 0);
    ~PlayWindow();

private:
    Ui::PlayWindow *ui;

    int id;
};

#endif // PLAYWINDOW_H
