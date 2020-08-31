#ifndef CONNETWINDOW_H
#define CONNETWINDOW_H

#include <QMainWindow>

namespace Ui {
class ConnetWindow;
}

class ConnetWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConnetWindow(QWidget *parent = nullptr);
    ~ConnetWindow();

private:
    Ui::ConnetWindow *ui;
};

#endif // CONNETWINDOW_H
