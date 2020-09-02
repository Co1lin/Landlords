#include "clientwindow.h"
#include "ui_clientwindow.h"

#include "playwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    clientSocket = new QTcpSocket();
    // connected with the server
    connect(clientSocket, &QTcpSocket::connected, [=]{ qDebug() << "connected"; });
    connect(clientSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,
           SLOT(displayError(QAbstractSocket::SocketError)));
    // "new data is available for reading from the device's current read channel"
    connect(clientSocket, &QTcpSocket::readyRead, this, &ClientWindow::readyRead);
    connect(&myTool, &MyTools::transferPackage, this, &ClientWindow::receivePackage);
    ui->pushButton->click();
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::on_pushButton_clicked()
{
    clientSocket->close();
    clientSocket->connectToHost(ui->hostLineEdit->text(), ui->portLineEdit->text().toInt());
    qDebug() << "Client connects to " << ui->hostLineEdit->text() << ": " << ui->portLineEdit->text().toInt();
}

void ClientWindow::displayError(QAbstractSocket::SocketError) //显示错误
{
    qDebug() << "error" << clientSocket->errorString();
    clientSocket->close();
}

void ClientWindow::receivePackage(DataPackage data)
{
    qDebug() << "Received id: " + QString::number(data.id);
//    QDataStream stream(clientSocket);
//    stream.setVersion(QDataStream::Qt_5_13);
//    int id;
//    stream >> id;
//    qDebug() << "Received id: " + QString::number(id);
    auto play = new PlayWindow(nullptr, data.id, clientSocket);
    play->setWindowTitle("Player " + QString::number(data.id));
    play->show();
    disconnect(clientSocket, &QTcpSocket::readyRead, this, &ClientWindow::readyRead);
    disconnect(&myTool, &MyTools::transferPackage, this, &ClientWindow::receivePackage);
    this->close();
}

void ClientWindow::clickConnectButton()
{
    ui->pushButton->click();
}

void ClientWindow::readyRead()
{
    myTool.read(clientSocket);
}
