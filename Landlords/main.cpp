#include "mainwindow.h"

#include <QApplication>

#include <connetwindow.h>
#include <playwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnetWindow connectWindow1;
    connectWindow1.show();

    ConnetWindow connectWindow2;
    connectWindow2.show();

    ConnetWindow connectWindow3;
    connectWindow3.show();

//    PlayWindow playWindow;
//    playWindow.show();

    return a.exec();
}
