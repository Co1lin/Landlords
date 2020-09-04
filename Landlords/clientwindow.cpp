#include "clientwindow.h"
#include "ui_clientwindow.h"

#include "playwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    setWindowTitle(QStringLiteral("Landlord - 斗地主 - 连接页面"));
    ui->infoLabel->setText(MyTools::getLocalIPString());
    clientSocket = new QTcpSocket();
    // connected with the server
    connect(clientSocket, &QTcpSocket::connected, [=]{ qDebug() << "connected"; });
    connect(clientSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,
           SLOT(displayError(QAbstractSocket::SocketError)));
    // "new data is available for reading from the device's current read channel"
    connect(clientSocket, &QTcpSocket::readyRead, this, &ClientWindow::readyRead);
    connect(&myTool, &MyTools::transferPackage, this, &ClientWindow::receivePackage);
    //ui->pushButton->click();
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::on_pushButton_clicked()
{
    clientSocket->close();
    clientSocket->connectToHost(ui->hostLineEdit->text(), ui->portSpinBox->text().toInt());
    //clientSocket->connectToHost(ui->hostLineEdit->text(), ui->portSpinBox->text().toInt(), QIODevice::ReadWrite, QAbstractSocket::IPv6Protocol);
    qDebug() << "Client connects to " << ui->hostLineEdit->text() << ": " << ui->portSpinBox->text().toInt();
    ui->pushButton->setEnabled(false);
}

void ClientWindow::setPort(const int port)
{
    ui->portSpinBox->setValue(port);
}

void ClientWindow::displayError(QAbstractSocket::SocketError) //显示错误
{
    qDebug() << "error" << clientSocket->errorString();
    clientSocket->close();
}

void ClientWindow::receivePackage(DataPackage data)
{
    qDebug() << "Received id: " + QString::number(data.id);
    auto play = new PlayWindow(nullptr, data.id, clientSocket, static_cast<bool>(data.msg[0].toInt()));
    // play->setWindowTitle("Player " + QString::number(data.id));
    play->move(this->pos());
    play->resize(this->size());
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
