/********************************************************************************
** Form generated from reading UI file 'playwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYWINDOW_H
#define UI_PLAYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGraphicsView *tableGraphicsView;
    QLabel *noticeLabel;
    QGraphicsView *player0GraphicsView;
    QGraphicsView *bottomCardsGraphicsView;
    QGraphicsView *player1GraphicsView;
    QGraphicsView *player2GraphicsView;
    QGraphicsView *myCardsGraphicsView;
    QPushButton *yesPushButton;
    QPushButton *noPushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PlayWindow)
    {
        if (PlayWindow->objectName().isEmpty())
            PlayWindow->setObjectName(QString::fromUtf8("PlayWindow"));
        PlayWindow->resize(800, 600);
        PlayWindow->setStyleSheet(QString::fromUtf8("#PlayWindow{border-image:url(:/images/bg.png);}\n"
"QGraphicsView{border:null;}"));
        centralwidget = new QWidget(PlayWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: transparent"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableGraphicsView = new QGraphicsView(centralwidget);
        tableGraphicsView->setObjectName(QString::fromUtf8("tableGraphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(tableGraphicsView->sizePolicy().hasHeightForWidth());
        tableGraphicsView->setSizePolicy(sizePolicy);
        tableGraphicsView->setLineWidth(0);
        QBrush brush(QColor(0, 0, 0, 0));
        brush.setStyle(Qt::NoBrush);
        tableGraphicsView->setBackgroundBrush(brush);

        gridLayout->addWidget(tableGraphicsView, 2, 1, 5, 6);

        noticeLabel = new QLabel(centralwidget);
        noticeLabel->setObjectName(QString::fromUtf8("noticeLabel"));
        noticeLabel->setStyleSheet(QString::fromUtf8("color: red"));
        noticeLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(noticeLabel, 7, 4, 1, 2);

        player0GraphicsView = new QGraphicsView(centralwidget);
        player0GraphicsView->setObjectName(QString::fromUtf8("player0GraphicsView"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(player0GraphicsView->sizePolicy().hasHeightForWidth());
        player0GraphicsView->setSizePolicy(sizePolicy1);
        QBrush brush1(QColor(0, 0, 0, 0));
        brush1.setStyle(Qt::NoBrush);
        player0GraphicsView->setBackgroundBrush(brush1);

        gridLayout->addWidget(player0GraphicsView, 4, 7, 3, 1);

        bottomCardsGraphicsView = new QGraphicsView(centralwidget);
        bottomCardsGraphicsView->setObjectName(QString::fromUtf8("bottomCardsGraphicsView"));
        bottomCardsGraphicsView->setLayoutDirection(Qt::LeftToRight);
        QBrush brush2(QColor(0, 0, 0, 0));
        brush2.setStyle(Qt::NoBrush);
        bottomCardsGraphicsView->setBackgroundBrush(brush2);
        bottomCardsGraphicsView->setInteractive(true);

        gridLayout->addWidget(bottomCardsGraphicsView, 0, 4, 1, 1);

        player1GraphicsView = new QGraphicsView(centralwidget);
        player1GraphicsView->setObjectName(QString::fromUtf8("player1GraphicsView"));
        QBrush brush3(QColor(0, 0, 0, 0));
        brush3.setStyle(Qt::NoBrush);
        player1GraphicsView->setBackgroundBrush(brush3);

        gridLayout->addWidget(player1GraphicsView, 0, 7, 1, 1);

        player2GraphicsView = new QGraphicsView(centralwidget);
        player2GraphicsView->setObjectName(QString::fromUtf8("player2GraphicsView"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(3);
        sizePolicy2.setHeightForWidth(player2GraphicsView->sizePolicy().hasHeightForWidth());
        player2GraphicsView->setSizePolicy(sizePolicy2);
        QBrush brush4(QColor(0, 0, 0, 0));
        brush4.setStyle(Qt::NoBrush);
        player2GraphicsView->setBackgroundBrush(brush4);

        gridLayout->addWidget(player2GraphicsView, 0, 1, 1, 1);

        myCardsGraphicsView = new QGraphicsView(centralwidget);
        myCardsGraphicsView->setObjectName(QString::fromUtf8("myCardsGraphicsView"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(6);
        sizePolicy3.setHeightForWidth(myCardsGraphicsView->sizePolicy().hasHeightForWidth());
        myCardsGraphicsView->setSizePolicy(sizePolicy3);
        myCardsGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        myCardsGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QBrush brush5(QColor(0, 0, 0, 0));
        brush5.setStyle(Qt::NoBrush);
        myCardsGraphicsView->setBackgroundBrush(brush5);

        gridLayout->addWidget(myCardsGraphicsView, 8, 0, 1, 8);

        yesPushButton = new QPushButton(centralwidget);
        yesPushButton->setObjectName(QString::fromUtf8("yesPushButton"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(yesPushButton->sizePolicy().hasHeightForWidth());
        yesPushButton->setSizePolicy(sizePolicy4);
        yesPushButton->setStyleSheet(QString::fromUtf8("#yesPushButton{\n"
"background-color: rgb(253, 128, 8);\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 20px;\n"
"border-width: 0px;\n"
"border-radius: 10px;\n"
"}\n"
"#yesPushButton:pressed\n"
"{\n"
"background-color: rgb(179, 98, 22);\n"
"}\n"
"#yesPushButton:disabled\n"
"{\n"
"background-color: rgb(102, 102, 102);\n"
"}"));

        gridLayout->addWidget(yesPushButton, 7, 7, 1, 1);

        noPushButton = new QPushButton(centralwidget);
        noPushButton->setObjectName(QString::fromUtf8("noPushButton"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(1);
        sizePolicy5.setHeightForWidth(noPushButton->sizePolicy().hasHeightForWidth());
        noPushButton->setSizePolicy(sizePolicy5);
        noPushButton->setStyleSheet(QString::fromUtf8("#noPushButton\n"
"{\n"
"color: white;\n"
"background-color: rgb(15, 128, 255);\n"
"font-weight: bold;\n"
"font-size: 20px;\n"
"border-width: 0px;\n"
"border-radius: 10px;\n"
"}\n"
"#noPushButton:disabled\n"
"{\n"
"background-color: #708090;\n"
"}\n"
"#noPushButton:pressed\n"
"{\n"
"background-color: rgb(71, 119, 179);\n"
"}"));

        gridLayout->addWidget(noPushButton, 7, 1, 1, 1);

        PlayWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PlayWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        PlayWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(PlayWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        PlayWindow->setStatusBar(statusbar);

        retranslateUi(PlayWindow);

        QMetaObject::connectSlotsByName(PlayWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PlayWindow)
    {
        PlayWindow->setWindowTitle(QCoreApplication::translate("PlayWindow", "MainWindow", nullptr));
        noticeLabel->setText(QString());
        yesPushButton->setText(QCoreApplication::translate("PlayWindow", "Yes", nullptr));
        noPushButton->setText(QCoreApplication::translate("PlayWindow", "No", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayWindow: public Ui_PlayWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYWINDOW_H
