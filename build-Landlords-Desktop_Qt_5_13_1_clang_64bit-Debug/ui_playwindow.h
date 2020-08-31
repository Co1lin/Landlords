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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGraphicsView *player1GraphicsView;
    QGraphicsView *player2GraphicsView;
    QGraphicsView *myCardsGraphicsView;
    QGraphicsView *cardsGraphicsView;
    QSpacerItem *verticalSpacer_3;
    QGraphicsView *player0GraphicsView;
    QLabel *noticeLabel;
    QPushButton *yesPushButton;
    QPushButton *noPushButton;
    QGraphicsView *bonusCardsGraphicsView;
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
        player1GraphicsView = new QGraphicsView(centralwidget);
        player1GraphicsView->setObjectName(QString::fromUtf8("player1GraphicsView"));

        gridLayout->addWidget(player1GraphicsView, 0, 8, 1, 1);

        player2GraphicsView = new QGraphicsView(centralwidget);
        player2GraphicsView->setObjectName(QString::fromUtf8("player2GraphicsView"));

        gridLayout->addWidget(player2GraphicsView, 0, 1, 1, 1);

        myCardsGraphicsView = new QGraphicsView(centralwidget);
        myCardsGraphicsView->setObjectName(QString::fromUtf8("myCardsGraphicsView"));

        gridLayout->addWidget(myCardsGraphicsView, 9, 0, 1, 9);

        cardsGraphicsView = new QGraphicsView(centralwidget);
        cardsGraphicsView->setObjectName(QString::fromUtf8("cardsGraphicsView"));

        gridLayout->addWidget(cardsGraphicsView, 2, 1, 5, 7);

        verticalSpacer_3 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer_3, 8, 1, 1, 1);

        player0GraphicsView = new QGraphicsView(centralwidget);
        player0GraphicsView->setObjectName(QString::fromUtf8("player0GraphicsView"));

        gridLayout->addWidget(player0GraphicsView, 6, 8, 1, 1);

        noticeLabel = new QLabel(centralwidget);
        noticeLabel->setObjectName(QString::fromUtf8("noticeLabel"));
        noticeLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(noticeLabel, 7, 5, 1, 2);

        yesPushButton = new QPushButton(centralwidget);
        yesPushButton->setObjectName(QString::fromUtf8("yesPushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(yesPushButton->sizePolicy().hasHeightForWidth());
        yesPushButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(yesPushButton, 7, 8, 1, 1);

        noPushButton = new QPushButton(centralwidget);
        noPushButton->setObjectName(QString::fromUtf8("noPushButton"));
        sizePolicy.setHeightForWidth(noPushButton->sizePolicy().hasHeightForWidth());
        noPushButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(noPushButton, 7, 1, 1, 1);

        bonusCardsGraphicsView = new QGraphicsView(centralwidget);
        bonusCardsGraphicsView->setObjectName(QString::fromUtf8("bonusCardsGraphicsView"));

        gridLayout->addWidget(bonusCardsGraphicsView, 0, 5, 1, 1);

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
