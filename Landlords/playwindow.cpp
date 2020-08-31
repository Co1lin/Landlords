#include "playwindow.h"
#include "ui_playwindow.h"

#include <QDebug>

PlayWindow::PlayWindow(QWidget *parent, const int _id) :
    QMainWindow(parent), id(_id),
    ui(new Ui::PlayWindow)
{
    ui->setupUi(this);
    qDebug() << "PlayWindow: " << id;
}

PlayWindow::~PlayWindow()
{
    delete ui;
}
