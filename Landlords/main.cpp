#include "mainwindow.h"

#include <QApplication>

#include <connetwindow.h>
#include <playwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnetWindow connectWindow1;
    connectWindow1.show();
    //connectWindow1.setMode("server");

    ConnetWindow connectWindow2;
    connectWindow2.show();
    //connectWindow2.setMode("client");

    ConnetWindow connectWindow3;
    connectWindow3.show();
    //connectWindow3.setMode("client");

    return a.exec();
}
