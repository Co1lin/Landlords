/********************************************************************************
** Form generated from reading UI file 'connetwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNETWINDOW_H
#define UI_CONNETWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnetWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *serverPushButton;
    QPushButton *clientPushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ConnetWindow)
    {
        if (ConnetWindow->objectName().isEmpty())
            ConnetWindow->setObjectName(QString::fromUtf8("ConnetWindow"));
        ConnetWindow->resize(800, 600);
        centralwidget = new QWidget(ConnetWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 2);

        serverPushButton = new QPushButton(centralwidget);
        serverPushButton->setObjectName(QString::fromUtf8("serverPushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(serverPushButton->sizePolicy().hasHeightForWidth());
        serverPushButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(serverPushButton, 1, 0, 1, 1);

        clientPushButton = new QPushButton(centralwidget);
        clientPushButton->setObjectName(QString::fromUtf8("clientPushButton"));
        sizePolicy1.setHeightForWidth(clientPushButton->sizePolicy().hasHeightForWidth());
        clientPushButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(clientPushButton, 1, 1, 1, 1);

        ConnetWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ConnetWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        ConnetWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ConnetWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ConnetWindow->setStatusBar(statusbar);

        retranslateUi(ConnetWindow);

        QMetaObject::connectSlotsByName(ConnetWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ConnetWindow)
    {
        ConnetWindow->setWindowTitle(QCoreApplication::translate("ConnetWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("ConnetWindow", "Please choose a working type:", nullptr));
        serverPushButton->setText(QCoreApplication::translate("ConnetWindow", "Server", nullptr));
        clientPushButton->setText(QCoreApplication::translate("ConnetWindow", "Client", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConnetWindow: public Ui_ConnetWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNETWINDOW_H
