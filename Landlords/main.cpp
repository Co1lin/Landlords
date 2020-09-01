#include "mainwindow.h"

#include <QApplication>

#include <connetwindow.h>
#include <playwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnetWindow connectWindow1;
    connectWindow1.show();
    connectWindow1.setMode("server");
    // std::this_thread::sleep_for(std::chrono::seconds(3)); //休眠三秒

    ConnetWindow connectWindow2;
    connectWindow2.show();
    connectWindow2.setMode("client");

    ConnetWindow connectWindow3;
    connectWindow3.show();
    connectWindow3.setMode("client");

//    PlayWindow playWindow;
//    playWindow.show();

    return a.exec();
}
