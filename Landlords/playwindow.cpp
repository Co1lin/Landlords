#include "playwindow.h"
#include "ui_playwindow.h"

PlayWindow::PlayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayWindow)
{
    ui->setupUi(this);
}

PlayWindow::~PlayWindow()
{
    delete ui;
}
