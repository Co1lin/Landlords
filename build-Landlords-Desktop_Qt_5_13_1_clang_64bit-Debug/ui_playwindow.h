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
    QGraphicsView *player2GraphicsView;
    QGraphicsView *tableGraphicsView;
    QGraphicsView *player1GraphicsView;
    QGraphicsView *myCardsGraphicsView;
    QLabel *noticeLabel;
    QGraphicsView *bottomCardsGraphicsView;
    QPushButton *yesPushButton;
    QPushButton *noPushButton;
    QGraphicsView *player0GraphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PlayWindow)
    {
        if (PlayWindow->objectName().isEmpty())
            PlayWindow->setObjectName(QString::fromUtf8("PlayWindow"));
        PlayWindow->resize(800, 600);
        centralwidget = new QWidget(PlayWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        player2GraphicsView = new QGraphicsView(centralwidget);
        player2GraphicsView->setObjectName(QString::fromUtf8("player2GraphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(3);
        sizePolicy.setHeightForWidth(player2GraphicsView->sizePolicy().hasHeightForWidth());
        player2GraphicsView->setSizePolicy(sizePolicy);
        QBrush brush(QColor(0, 0, 0, 0));
        brush.setStyle(Qt::NoBrush);
        player2GraphicsView->setBackgroundBrush(brush);

        gridLayout->addWidget(player2GraphicsView, 0, 1, 1, 1);

        tableGraphicsView = new QGraphicsView(centralwidget);
        tableGraphicsView->setObjectName(QString::fromUtf8("tableGraphicsView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(tableGraphicsView->sizePolicy().hasHeightForWidth());
        tableGraphicsView->setSizePolicy(sizePolicy1);
        QBrush brush1(QColor(0, 0, 0, 0));
        brush1.setStyle(Qt::NoBrush);
        tableGraphicsView->setBackgroundBrush(brush1);

        gridLayout->addWidget(tableGraphicsView, 2, 1, 5, 6);

        player1GraphicsView = new QGraphicsView(centralwidget);
        player1GraphicsView->setObjectName(QString::fromUtf8("player1GraphicsView"));
        QBrush brush2(QColor(0, 0, 0, 0));
        brush2.setStyle(Qt::NoBrush);
        player1GraphicsView->setBackgroundBrush(brush2);

        gridLayout->addWidget(player1GraphicsView, 0, 7, 1, 1);

        myCardsGraphicsView = new QGraphicsView(centralwidget);
        myCardsGraphicsView->setObjectName(QString::fromUtf8("myCardsGraphicsView"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(6);
        sizePolicy2.setHeightForWidth(myCardsGraphicsView->sizePolicy().hasHeightForWidth());
        myCardsGraphicsView->setSizePolicy(sizePolicy2);
        QBrush brush3(QColor(0, 0, 0, 0));
        brush3.setStyle(Qt::NoBrush);
        myCardsGraphicsView->setBackgroundBrush(brush3);

        gridLayout->addWidget(myCardsGraphicsView, 8, 0, 1, 8);

        noticeLabel = new QLabel(centralwidget);
        noticeLabel->setObjectName(QString::fromUtf8("noticeLabel"));
        noticeLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(noticeLabel, 7, 4, 1, 2);

        bottomCardsGraphicsView = new QGraphicsView(centralwidget);
        bottomCardsGraphicsView->setObjectName(QString::fromUtf8("bottomCardsGraphicsView"));
        bottomCardsGraphicsView->setLayoutDirection(Qt::LeftToRight);
        QBrush brush4(QColor(0, 0, 0, 0));
        brush4.setStyle(Qt::NoBrush);
        bottomCardsGraphicsView->setBackgroundBrush(brush4);
        bottomCardsGraphicsView->setInteractive(true);

        gridLayout->addWidget(bottomCardsGraphicsView, 0, 4, 1, 1);

        yesPushButton = new QPushButton(centralwidget);
        yesPushButton->setObjectName(QString::fromUtf8("yesPushButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(yesPushButton->sizePolicy().hasHeightForWidth());
        yesPushButton->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(yesPushButton, 7, 7, 1, 1);

        noPushButton = new QPushButton(centralwidget);
        noPushButton->setObjectName(QString::fromUtf8("noPushButton"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(1);
        sizePolicy4.setHeightForWidth(noPushButton->sizePolicy().hasHeightForWidth());
        noPushButton->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(noPushButton, 7, 1, 1, 1);

        player0GraphicsView = new QGraphicsView(centralwidget);
        player0GraphicsView->setObjectName(QString::fromUtf8("player0GraphicsView"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(player0GraphicsView->sizePolicy().hasHeightForWidth());
        player0GraphicsView->setSizePolicy(sizePolicy5);
        QBrush brush5(QColor(0, 0, 0, 0));
        brush5.setStyle(Qt::NoBrush);
        player0GraphicsView->setBackgroundBrush(brush5);

        gridLayout->addWidget(player0GraphicsView, 4, 7, 3, 1);

        PlayWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PlayWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
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
        noticeLabel->setText(QCoreApplication::translate("PlayWindow", "Notice", nullptr));
        yesPushButton->setText(QCoreApplication::translate("PlayWindow", "Yes", nullptr));
        noPushButton->setText(QCoreApplication::translate("PlayWindow", "No", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayWindow: public Ui_PlayWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYWINDOW_H
