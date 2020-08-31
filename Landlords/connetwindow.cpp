#include "connetwindow.h"
#include "ui_connetwindow.h"

ConnetWindow::ConnetWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnetWindow)
{
    ui->setupUi(this);
}

ConnetWindow::~ConnetWindow()
{
    delete ui;
}
