#include "playwindow.h"
#include "ui_playwindow.h"

#include <QDebug>
#include "mytools.h"

PlayWindow::PlayWindow(QWidget *parent, const int _id, QTcpSocket* _socket, const bool _firstMusic) :
    QMainWindow(parent),
    ui(new Ui::PlayWindow),
    id(_id),
    playSocket(_socket)
{
    ui->setupUi(this);
    // UI
    qDebug() << "PlayWindow: " << id;
    setWindowTitle(QStringLiteral("斗地主 Landlord - Player ") + QString::number(id));
    firstMusic = _firstMusic;
    //thisTrun = false;
    ui->noticeLabel->setFont(QFont(QStringLiteral("黑体"), 20));
    ui->yesPushButton->setEnabled(false);
    ui->noPushButton->setEnabled(false);
    myTool.installMyEventFilter(&bottomCardsGraphicsScene);
    myTool.installMyEventFilter(&tableGraphicsScene);
    ui->myCardsGraphicsView->setStyleSheet("background: transparent");
    ui->bottomCardsGraphicsView->setStyleSheet("background: transparent");
    ui->tableGraphicsView->setStyleSheet("background: transparent");
    ui->player0GraphicsView->setStyleSheet("background: transparent");
    ui->player1GraphicsView->setStyleSheet("background: transparent");
    ui->player2GraphicsView->setStyleSheet("background: transparent");
    ui->myCardsGraphicsView->setScene(&myCardsGraphicsScene);
    ui->bottomCardsGraphicsView->setScene(&bottomCardsGraphicsScene);
    ui->tableGraphicsView->setScene(&tableGraphicsScene);
    for (int i = 0; i <= 2; i++)
        playersInfoScene.push_back(new QGraphicsScene());
    ui->player0GraphicsView->setScene(playersInfoScene[id]);
    ui->player1GraphicsView->setScene(playersInfoScene[MyTools::nextId(id)]);
    ui->player2GraphicsView->setScene(playersInfoScene[MyTools::nextId(MyTools::nextId(id))]);
    ui->myCardsGraphicsView->show();
    ui->bottomCardsGraphicsView->show();
    ui->tableGraphicsView->show();
    ui->player0GraphicsView->show();
    ui->player1GraphicsView->show();
    ui->player2GraphicsView->show();
    connect(&fitTimer, &QTimer::timeout, this, &PlayWindow::fitView);
    fitTimer.start(33);
    // network
    DataPackage confirmReady(id);
    confirmReady.type = 0;
    myTool.send(playSocket, confirmReady);
    // sticky package test
    myTool.send(playSocket, confirmReady);
    connect(playSocket, &QTcpSocket::readyRead, this, &PlayWindow::readyRead);
    connect(&myTool, &MyTools::transferPackage, this, &PlayWindow::receivePackage);
}

PlayWindow::~PlayWindow()
{
    delete ui;
}

void PlayWindow::playMusic()
{
    playlist.addMedia(QUrl("qrc:/media/normal.mp3"));
    playlist.addMedia(QUrl("qrc:/media/electronic.mp3"));
    player.setPlaylist(&playlist);
    if (firstMusic)
        playlist.next();
    player.play();
}

void PlayWindow::receivePackage(DataPackage data)
{
    qDebug() << "id: " << id;
    if (data.type == 1) // receive dealed 17 cards
    {
        // music
        playMusic();
        // data.sortCards();
        foreach (auto& card, data.cards)
        {
            qDebug() << card.name();
        }
        myCards = std::move(data.cards);
        showCards();
        showPlayersInfo(data);
        DataPackage dataToSend(id);
        dataToSend.type = 1;
        myTool.send(playSocket, dataToSend);
    }
    else if (data.type == 3)    // decide the landlord
    {
        if (data.msg[0] == "landlord?")
        {
            qDebug() << QStringLiteral("叫地主？");
            ui->noticeLabel->setText(QStringLiteral("叫地主？"));
            enableChoice();
        }
        else if (data.msg[0] == "landlord??")
        {
            ui->noticeLabel->setText(QStringLiteral("抢地主？"));
            enableChoice();
        }
        else if (data.msg[0] == "have landlord")    // have decide the landlord
        {
            showPlayersInfo(data);
            // show the bottom cards
            int i = 0;
            foreach (auto& card, data.cards)
            {
                auto cardItem = new CardItem(card);
                // bottomCardsGraphicsScene.clear();
                bottomCardsGraphicsScene.addItem(cardItem);
                cardItem->setPos(i * 100, 0);
                i++;
            }
            if (data.playerInfo[id].role == QStringLiteral("地主"))  // I am the landlords!
            {
                // add three cards
                myCards << data.cards;
                std::sort(myCards.begin(), myCards.end(), std::greater<Card>());
                showCards();
                // play cards first
                ui->noticeLabel->setText(QStringLiteral("请出牌"));
                ui->yesPushButton->setEnabled(true);
            }
        }
    }
    else if (data.type == 2)    // playing game
    {
        showPlayersInfo(data);
        showTableCards(data);
        tmpData = data;
        if (data.msg.size() == 2 && data.msg.last() == "passed")
        {
            auto passed = new QGraphicsTextItem();
            passed->setFont(QFont(QStringLiteral("黑体"), 30));
            passed->setHtml(QStringLiteral("<p>上一玩家不出</p>"));
            tableGraphicsScene.addItem(passed);
            passed->setPos(tableGraphicsScene.sceneRect().width() / 2, 0);
        }
        if (data.msg[0] == "wait")
        {
            // nothing
        }
        else if (data.msg[0] == "your turn")
        {
            enableChoice();
            if (data.cards.empty())
                ui->noPushButton->setEnabled(false);
            ui->noticeLabel->setText(QStringLiteral("请出牌"));
        }
        else if (data.msg[0] == "end!")
        {
            if (data.playerInfo[id].role == data.msg[1])
                ui->noticeLabel->setText(data.msg[1] + QStringLiteral("获胜！") + QStringLiteral("    重新开始？"));
            else
                ui->noticeLabel->setText(data.playerInfo[id].role + QStringLiteral("输了(o_ _)ﾉ") + QStringLiteral("    重新开始？"));
            enableChoice();
        }
    }
}

void PlayWindow::showCards()
{
    myCardsGraphicsScene.clear();
    addBlock();
    MyTools::sortCards(myCards);
    int i = 0;
    foreach(auto& card, myCards)
    {
        auto cardItem = new CardItem(card);
        myCardsGraphicsScene.addItem(cardItem);
        cardItem->setPos(i * 60, 55);
        i++;
    }
}

void PlayWindow::showPlayersInfo(const DataPackage& data, const int _id)
{
    if (_id == -1)
    {
        for (int i = 0; i <= 2; i++)
        {
            playersInfoScene[i]->clear();
            auto playerInfo = new PlayerInfo(data.playerInfo[i]);
            if (i == id)
                playerInfo->setNote("(Me)");
            playersInfoScene[i]->addItem(playerInfo);
        }
    }
    else
    {
        playersInfoScene[_id]->clear();
        auto playerInfo = new PlayerInfo(data.playerInfo[_id]);
        if (_id == id)
            playerInfo->setNote("(Me)");
        playersInfoScene[_id]->addItem(playerInfo);
    }
}

void PlayWindow::showTableCards(const DataPackage &data)
{
    tableGraphicsScene.clear();
    auto tableBlock = new QGraphicsRectItem(0, 0, 100, 50);
    tableGraphicsScene.addItem(tableBlock);
    tableBlock->setPen(QPen(Qt::transparent));
    tableBlock->setPos(0, 0);
    int i = 0;
    foreach (auto card, data.cards)
    {
        auto cardItem = new CardItem(card);
        tableGraphicsScene.addItem(cardItem);
        cardItem->setPos(i * 100, 55);
        i++;
    }
}

void PlayWindow::fitView()
{
    // qDebug() << "fitView!";
    auto rect = myCardsGraphicsScene.sceneRect();
    auto delta = rect.height() / 10;
    rect.setHeight(rect.height() + delta);
    ui->myCardsGraphicsView->setAlignment(Qt::AlignCenter);
    ui->myCardsGraphicsView->fitInView(myCardsGraphicsScene.sceneRect(), Qt::KeepAspectRatio);

    ui->bottomCardsGraphicsView->fitInView(bottomCardsGraphicsScene.sceneRect(), Qt::KeepAspectRatio);

    rect = tableGraphicsScene.sceneRect();
    delta = rect.height() / 8;
    rect.setHeight(rect.height() + delta);
    ui->tableGraphicsView->fitInView(rect, Qt::KeepAspectRatio);

    ui->player0GraphicsView->fitInView(playersInfoScene[id]->sceneRect(), Qt::KeepAspectRatio);
    ui->player1GraphicsView->fitInView(playersInfoScene[MyTools::nextId(id)]->sceneRect(), Qt::KeepAspectRatio);
    ui->player2GraphicsView->fitInView(playersInfoScene[MyTools::nextId(MyTools::nextId(id))]->sceneRect(), Qt::KeepAspectRatio);
}

void PlayWindow::addBlock()
{
    block = new QGraphicsRectItem(0, 0, 50, 50);
    myCardsGraphicsScene.addItem(block);
    block->setPen(QPen(Qt::transparent));
    block->setPos(0, 0);
}

void PlayWindow::enableChoice()
{
    ui->yesPushButton->setEnabled(true);
    ui->noPushButton->setEnabled(true);
}

void PlayWindow::disableChoice()
{
    ui->yesPushButton->setEnabled(false);
    ui->noPushButton->setEnabled(false);
}

void PlayWindow::on_yesPushButton_clicked()
{
    if (ui->noticeLabel->text() == QStringLiteral("叫地主？") ||
        ui->noticeLabel->text() == QStringLiteral("抢地主？"))
    {
        DataPackage dataToSend(id);
        dataToSend.type = 3;
        dataToSend.msg << "yes";
        myTool.send(playSocket, dataToSend);
    }
    else if (ui->noticeLabel->text() == QStringLiteral("请出牌") ||
             ui->noticeLabel->text() == QStringLiteral("出牌不符合规则！"))
    {
        if (beat(tmpData.cards))
        {
            DataPackage dataToSend(id);
            dataToSend.type = 2;
            dataToSend.msg << "play";
            dataToSend.cards = selectedCards;
            qDebug() << "send cards!";
            // delete the cards that the player played
            foreach (auto item, selectedCardItems)
            {
                int index = myCards.indexOf(item->getCard());
                myCards.erase(myCards.begin() + index);
                myCardsGraphicsScene.removeItem(item);
            }
            // update the view of my cards
            showCards();
            if (myCards.empty())    // WIN!!!
                dataToSend.msg << "WIN!";
            myTool.send(playSocket, dataToSend);    // send cards!
        }
        else
        {
            ui->noticeLabel->setText(QStringLiteral("出牌不符合规则！"));
            return;
        }
    }
    else if (ui->noticeLabel->text().mid(0, 2) == QStringLiteral("农民") ||
             ui->noticeLabel->text().mid(0, 2) == QStringLiteral("地主"))
    {
        // restart
        disconnect(&fitTimer, &QTimer::timeout, this, &PlayWindow::fitView);
        disconnect(playSocket, &QTcpSocket::readyRead, this, &PlayWindow::readyRead);
        disconnect(&myTool, &MyTools::transferPackage, this, &PlayWindow::receivePackage);
        player.stop();
        auto play = new PlayWindow(nullptr, id, playSocket, !firstMusic);
        play->setWindowTitle("Player " + QString::number(id));
        play->move(this->pos());
        play->resize(this->size());
        play->show();
        this->close();
    }
    ui->noticeLabel->setText(QStringLiteral("等待"));
    disableChoice();
}

void PlayWindow::on_noPushButton_clicked()
{
    if (ui->noticeLabel->text() == QStringLiteral("叫地主？") ||
        ui->noticeLabel->text() == QStringLiteral("抢地主？"))
    {
        DataPackage dataToSend(id);
        dataToSend.type = 3;
        dataToSend.msg << "no";
        myTool.send(playSocket, dataToSend);
    }
    else if (ui->noticeLabel->text() == QStringLiteral("请出牌") ||
             ui->noticeLabel->text() == QStringLiteral("出牌不符合规则！"))
    {
        // pass
        DataPackage dataToSend(id);
        dataToSend.type = 2;
        dataToSend.msg << "pass";
        myTool.send(playSocket, dataToSend);
    }
    else if (ui->noticeLabel->text().mid(0, 2) == QStringLiteral("农民") ||
             ui->noticeLabel->text().mid(0, 2) == QStringLiteral("地主"))
    {
        exit(0);
    }
    ui->noticeLabel->setText(QStringLiteral("等待"));
    disableChoice();
}

bool PlayWindow::beat(const QList<Card>& _lastCards)
{
    // get all cards selected
    selectedCards.clear();
    selectedCardItems.clear();
    auto cardItems = myCardsGraphicsScene.items();
    foreach (QGraphicsItem* item, cardItems)
    {
        auto cardItem = dynamic_cast<CardItem*>(item);
        if (cardItem && cardItem->isSelected())
        {
            selectedCards << cardItem->getCard();
            selectedCardItems << cardItem;
        }
    }
    if (selectedCards.empty())
        return false;
    else
        MyTools::sortCards(selectedCards);

    qDebug() << "judgement!!!!!!!!!!!!!!!!!!!!!!!!";
    QString selectedCardsType = cardsType(selectedCards);
    qDebug() << selectedCardsType;
    if (myCards.size() == 20 || _lastCards.empty())
    {
        if (selectedCardsType != "invalid" && selectedCardsType != "!invalid!")
            return true;
        else
            return false;
    }
    else
    {
        QString lastCardsType = cardsType(_lastCards);
        if (selectedCardsType != lastCardsType)
        {
            if (selectedCardsType == "double king")
                return true;
            else if (selectedCardsType == "bomb" && lastCardsType != "double king")
                return true;
            else
                return false;
        }
        else
        {
            if (selectedCardsType == "single" ||
                selectedCardsType == "double")
                return selectedCards.first() > _lastCards.first();
            else if (selectedCardsType.mid(1) == "straight" ||
                     selectedCardsType.mid(1) == "double straight")
                return selectedCards.last() > _lastCards.last();
            else if (selectedCardsType.mid(1, 6) == "triple" ||
                     selectedCardsType.mid(0, 4) == "bomb")
            {
                auto same1 = MyTools::maxSame(selectedCards);
                auto same2 = MyTools::maxSame(_lastCards);
                return same1.first > same2.first;
            }
        }
    }
}

QString PlayWindow::cardsType(const QList<Card>& cards)
{
    /*  null
     *  invalid
     *  single
     *  straight            5straight ...
     *  double
     *  double king
     *  double straight     5double straight ...
     *  triple * n
     *      + 0             4triple
     *      + single * 1    4triple+single  ...
     *      + double * 1    4triple+double  ...
     *  bomb
     *      +single*2       bomb+2single
     *      +double*2       bomb+2double
     */

    if (cards.empty())
        return "null";
    else if (cards.size() == 1)
        return "single";
    else if (cards.size() == 2)
    {
        if (cards.first() == cards.last())
            return "double";
        else if (cards.first().number == 17 &&
                 cards.last().number == 16)
            return "double king";
        else
            return "invalid";
    }
    else if (cards.size() == 3)
    {
        if (cards.first() == cards.last() &&
            cards.first() == cards.value(1))
            return "1triple";
        else
            return "invalid";
    }
    else if (cards.size() == 4)
    {
        if (cards.first() == cards.last() &&
            cards.first() == cards.value(1) &&
            cards.first() == cards.value(2))
            return "bomb";
        else
        {
            auto myPair = MyTools::maxSame(cards);
            if (myPair.second == 3)
            {
                return "1triple";
            }
            else
                return "invalid";
        }
    }
    else if (cards.size() == 5)
    {
        // 333 + 44 or 34567
        auto myPair = MyTools::maxSame(cards);
        if (myPair.second == 3)
        {
            QVector<int> others;
            foreach (auto& card, cards)
            {
                if (card.number != myPair.first)
                    others << card.number;
            }
            if (others.first() == others.last())
                return "1triple+double";
            else
                return "invalid";
        }
        else if (myPair.second == 1)
        {
            myPair = MyTools::hasStraignt(cards);
            if (myPair.first != -1 && myPair.second - myPair.first + 1 == 5)
                return "5straight";
            else
                return "invalid";
        }
        else
            return "invalid";
    }
    else if (cards.size() == 6)
    {
        auto myMap = MyTools::makeMap(cards);
        auto myPair = MyTools::maxSame(cards);
        if (myPair.second == 4)
        {
            return "bomb+2single";
        }
        else if (myPair.second == 3)
        {
            if (myMap.size() == 2)
            {
                QList<int> tripleStraight;
                for (auto iter = myMap.begin(); iter != myMap.end(); iter++)
                    tripleStraight << iter.key();
                auto straight = MyTools::hasStraignt(tripleStraight);
                if (straight.first != -1)
                    return "2triple";
                else
                    return "invalid";
            }
            else
                return "invalid";
        }
        else if (myPair.second == 2)
        {
            if (myMap.size() == 3)
            {   // 334455 ?
                auto straight = MyTools::hasStraignt({ cards.first(), cards.value(2), cards.last() });
                if (straight.first != -1)
                    return "3double straight";
                else
                    return "invalid";
            }
            else
                return "invalid";
        }
        else if (myPair.second == 1)
        {
            auto straight = MyTools::hasStraignt(cards);
            if (straight.first != -1)
                return "6straight";
            else
                return "invalid";
        }
        else
            return "invalid";
    }
    else if (cards.size() == 7)
    {
        auto myPair = MyTools::maxSame(cards);
        if (myPair.second == 1)
        {
            auto straight = MyTools::hasStraignt(cards);
            if (straight.first != -1)
                return "6straight";
            else
                return "invalid";
        }
        else
            return "invalid";
    }
    else if (cards.size() >= 8)
    {
        // 333444 79
        // 44556677
        // 333444555
        // 333444555666777888
        // 3456789(10)
        // 4444 55 77
        QMap<int, QString> hex;
        for (int i = 1; i <= 9; i++)
            hex[i] = QString::number(i);
        hex[10] = "A";
        hex[11] = "B";
        hex[12] = "C";
        auto straight = MyTools::hasStraignt(cards);
        if (straight.first != -1)
        {
            return hex[cards.size()] + "straight";
        }
        else
        {
            QVector<QPair<int, int>> same;
            QList<Card> others = cards;
            while (others.size())
            {
                same << MyTools::maxSame(others);
                for (auto iter = others.begin(); iter != others.end(); )
                {
                    if (iter->number == same.last().first)
                        iter = others.erase(iter);
                    else
                        iter++;
                }
            }
            if (cards.size() % 2 == 0 && same.first().second == 2)
            {
                QList<Card> list1, list2;
                int j = 0;
                for (int i = 0; i < cards.size() - 1; i += 2)
                {
                    list1 << cards.value(i);
                    if (cards.value(i) == cards.value(i + 1))
                    {
                        list2 << cards.value(i + 1);
                        j++;
                    }
                    else if (j >= 5)
                        return "invalid";
                    else
                    {
                        j = -1;
                        break;
                    }
                }
                straight = MyTools::hasStraignt(list1);
                if (j >= 4 && straight.first != -1 && list1 == list2)
                {
                    return hex[j] + "double straight";
                }
            }
//            QVector<QPair<int, int>> same;
//            QList<Card> others = cards;
//            while (others.size())
//            {
//                same << MyTools::maxSame(others);
//                for (auto iter = others.begin(); iter != others.end(); )
//                {
//                    if (iter->number == same.last().first)
//                        iter = others.erase(iter);
//                    else
//                        iter++;
//                }
//            }
            else if (cards.size() == 8 && same.first().second == 4 && same.size() == 3)
            {
                if (same.last().second == 2 && same.value(1).second == 2)
                    return "bomb+2double";
                else
                    return "invalid";
            }
            else if (same.first().second == 3)
            {
                int cc = 0;
                foreach (auto pair, same)
                {
                    if (pair.second != 3)
                        break;
                    else
                        cc++;
                }
                if (cc == 0)
                    return "invalid";
                QList<int> tripleStraight;
                for (int i = 0; i < cc; i++)
                {
                    tripleStraight << same[i].first;
                }
                straight = MyTools::hasStraignt(tripleStraight);
                if (straight.first != -1)
                {
                    if (cc == same.size())
                        return hex[cc] + "triple";
                    else
                    {
                        int j = 1;
                        for (auto iter = same.rbegin() + 1; iter != same.rend(); iter++)
                        {
                            if (iter->second == 3)
                                break;
                            else if (j > cc)
                                return "invalid";
                            else
                            {
                                if (iter->second != same.last().second)
                                    return "invalid";
                                else
                                    j++;
                            }
                        }
                        if (j == cc)
                            return hex[cc] + "triple";
                        else
                            return "!invalid!";
                    }
                }
                else
                    return "invalid";
            }
        }
    }
    return "!invalid!";
}

void PlayWindow::readyRead()
{
    myTool.read(playSocket);
}
