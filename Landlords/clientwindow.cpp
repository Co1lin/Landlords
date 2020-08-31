#include "clientwindow.h"
#include "ui_clientwindow.h"

#include "playwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    client = new QTcpSocket();
    connect(client, &QTcpSocket::connected, [=]{ qDebug() << "connected"; });
    connect(client,SIGNAL(error(QAbstractSocket::SocketError)),this,
           SLOT(displayError(QAbstractSocket::SocketError)));
    connect(client, &QTcpSocket::readyRead, this, &ClientWindow::readMessage);
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::on_pushButton_clicked()
{
    client->close();
    client->connectToHost(ui->hostLineEdit->text(), ui->portLineEdit->text().toInt());
    qDebug() << "Client connects to " << ui->hostLineEdit->text() << ": " << ui->portLineEdit->text().toInt();
}

void ClientWindow::displayError(QAbstractSocket::SocketError) //显示错误
{
    qDebug() << client->errorString();
    client->close();
}

void ClientWindow::readMessage()
{
    QDataStream stream(client);
    stream.setVersion(QDataStream::Qt_5_13);
    QString id;
    stream >> id;
    qDebug() << "Received id: " + id;
    auto play = new PlayWindow(nullptr, id.toInt());
    play->setWindowTitle("Player " + id);
    play->show();
    this->close();
}
