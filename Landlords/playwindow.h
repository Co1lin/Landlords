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
    explicit PlayWindow(QWidget *parent = nullptr);
    ~PlayWindow();

private:
    Ui::PlayWindow *ui;
};

#endif // PLAYWINDOW_H
