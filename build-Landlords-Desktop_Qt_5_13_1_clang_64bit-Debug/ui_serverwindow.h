/********************************************************************************
** Form generated from reading UI file 'serverwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERWINDOW_H
#define UI_SERVERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QListWidget *listWidget;
    QLabel *label;
    QLabel *infoLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ServerWindow)
    {
        if (ServerWindow->objectName().isEmpty())
            ServerWindow->setObjectName(QString::fromUtf8("ServerWindow"));
        ServerWindow->resize(800, 600);
        centralwidget = new QWidget(ServerWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(280, 430, 231, 71));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(270, 210, 256, 192));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 40, 251, 61));
        label->setAlignment(Qt::AlignCenter);
        infoLabel = new QLabel(centralwidget);
        infoLabel->setObjectName(QString::fromUtf8("infoLabel"));
        infoLabel->setGeometry(QRect(270, 120, 251, 61));
        infoLabel->setAlignment(Qt::AlignCenter);
        ServerWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ServerWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        ServerWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ServerWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ServerWindow->setStatusBar(statusbar);

        retranslateUi(ServerWindow);

        QMetaObject::connectSlotsByName(ServerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ServerWindow)
    {
        ServerWindow->setWindowTitle(QCoreApplication::translate("ServerWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("ServerWindow", "Start Listening", nullptr));
        label->setText(QCoreApplication::translate("ServerWindow", "Local Infomation:", nullptr));
        infoLabel->setText(QCoreApplication::translate("ServerWindow", "?:?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerWindow: public Ui_ServerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERWINDOW_H
