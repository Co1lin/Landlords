#include "connetwindow.h"
#include "ui_connetwindow.h"

#include "serverwindow.h"
#include "clientwindow.h"

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

void ConnetWindow::on_serverPushButton_clicked()
{
    auto serverWindow = new ServerWindow();
    serverWindow->show();
    this->close();
}

void ConnetWindow::on_clientPushButton_clicked()
{
    auto clientWindow = new ClientWindow();
    clientWindow->show();
    this->close();
}
