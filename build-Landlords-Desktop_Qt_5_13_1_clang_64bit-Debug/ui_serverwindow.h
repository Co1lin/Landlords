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
#include <QtWidgets/QSpinBox>
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
    QLabel *label_2;
    QSpinBox *portSpinBox;
    QListWidget *infoListWidget;
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
        listWidget->setGeometry(QRect(270, 220, 256, 91));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 30, 251, 61));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(270, 300, 251, 61));
        label_2->setAlignment(Qt::AlignCenter);
        portSpinBox = new QSpinBox(centralwidget);
        portSpinBox->setObjectName(QString::fromUtf8("portSpinBox"));
        portSpinBox->setGeometry(QRect(330, 360, 141, 51));
        portSpinBox->setMinimum(6666);
        portSpinBox->setMaximum(49151);
        infoListWidget = new QListWidget(centralwidget);
        infoListWidget->setObjectName(QString::fromUtf8("infoListWidget"));
        infoListWidget->setGeometry(QRect(270, 80, 256, 131));
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
        pushButton->setText(QCoreApplication::translate("ServerWindow", "\345\274\200\346\210\277\351\227\264\345\271\266\347\255\211\345\276\205\345\205\266\345\256\203\347\216\251\345\256\266\350\277\233\345\205\245\n"
"Start Listening", nullptr));
        label->setText(QCoreApplication::translate("ServerWindow", "Local Infomation:", nullptr));
        label_2->setText(QCoreApplication::translate("ServerWindow", "Listen port:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerWindow: public Ui_ServerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERWINDOW_H
