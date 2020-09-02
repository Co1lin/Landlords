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
    QGraphicsView *cardsGraphicsView;
    QGraphicsView *player1GraphicsView;
    QGraphicsView *myCardsGraphicsView;
    QLabel *noticeLabel;
    QGraphicsView *bonusCardsGraphicsView;
    QPushButton *yesPushButton;
    QGraphicsView *player0GraphicsView;
    QPushButton *noPushButton;
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
        sizePolicy.setVerticalStretch(2);
        sizePolicy.setHeightForWidth(player2GraphicsView->sizePolicy().hasHeightForWidth());
        player2GraphicsView->setSizePolicy(sizePolicy);

        gridLayout->addWidget(player2GraphicsView, 0, 1, 1, 1);

        cardsGraphicsView = new QGraphicsView(centralwidget);
        cardsGraphicsView->setObjectName(QString::fromUtf8("cardsGraphicsView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cardsGraphicsView->sizePolicy().hasHeightForWidth());
        cardsGraphicsView->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(cardsGraphicsView, 2, 1, 5, 6);

        player1GraphicsView = new QGraphicsView(centralwidget);
        player1GraphicsView->setObjectName(QString::fromUtf8("player1GraphicsView"));

        gridLayout->addWidget(player1GraphicsView, 0, 7, 1, 1);

        myCardsGraphicsView = new QGraphicsView(centralwidget);
        myCardsGraphicsView->setObjectName(QString::fromUtf8("myCardsGraphicsView"));
        sizePolicy.setHeightForWidth(myCardsGraphicsView->sizePolicy().hasHeightForWidth());
        myCardsGraphicsView->setSizePolicy(sizePolicy);

        gridLayout->addWidget(myCardsGraphicsView, 8, 0, 1, 8);

        noticeLabel = new QLabel(centralwidget);
        noticeLabel->setObjectName(QString::fromUtf8("noticeLabel"));
        noticeLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(noticeLabel, 7, 4, 1, 2);

        bonusCardsGraphicsView = new QGraphicsView(centralwidget);
        bonusCardsGraphicsView->setObjectName(QString::fromUtf8("bonusCardsGraphicsView"));

        gridLayout->addWidget(bonusCardsGraphicsView, 0, 4, 1, 1);

        yesPushButton = new QPushButton(centralwidget);
        yesPushButton->setObjectName(QString::fromUtf8("yesPushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(yesPushButton->sizePolicy().hasHeightForWidth());
        yesPushButton->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(yesPushButton, 7, 7, 1, 1);

        player0GraphicsView = new QGraphicsView(centralwidget);
        player0GraphicsView->setObjectName(QString::fromUtf8("player0GraphicsView"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(player0GraphicsView->sizePolicy().hasHeightForWidth());
        player0GraphicsView->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(player0GraphicsView, 6, 7, 1, 1);

        noPushButton = new QPushButton(centralwidget);
        noPushButton->setObjectName(QString::fromUtf8("noPushButton"));
        sizePolicy2.setHeightForWidth(noPushButton->sizePolicy().hasHeightForWidth());
        noPushButton->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(noPushButton, 7, 1, 1, 1);

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
