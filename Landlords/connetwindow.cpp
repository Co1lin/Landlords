#include "connetwindow.h"
#include "ui_connetwindow.h"

#include "serverwindow.h"
#include "clientwindow.h"

ConnetWindow::ConnetWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnetWindow)
{
    ui->setupUi(this);
    setWindowTitle(QStringLiteral("Landlord - 斗地主 - 连接页面"));
}

ConnetWindow::~ConnetWindow()
{
    delete ui;
}

void ConnetWindow::on_serverPushButton_clicked()
{
    auto serverWindow = new ServerWindow();
    serverWindow->move(this->pos());
    serverWindow->resize(this->size());
    serverWindow->show();
    this->close();
}

void ConnetWindow::on_clientPushButton_clicked()
{
    auto clientWindow = new ClientWindow();
    clientWindow->move(this->pos());
    clientWindow->resize(this->size());
    clientWindow->show();
    this->close();
}

void ConnetWindow::setMode(const QString &mode)
{
    if (mode == "server")
        ui->serverPushButton->click();
    if (mode == "client")
        ui->clientPushButton->click();
}
