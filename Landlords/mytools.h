#ifndef MYTOOLS_H
#define MYTOOLS_H

#include <QtNetwork>
#include <QGraphicsItem>


class Card
{
public:
    Card() {}
    Card (const QChar &_pattern, const int _number):
        pattern(_pattern), number(_number)
    {}

public:
    QChar pattern;
    /*
     * king:    0
     * spade:   1
     * heart:   2
     * club:    3
     * diamond: 4
     */
    int number;
    /*
     * 3 ~ 17
     * A:               14
     * 2:               15
     * black joker:     16
     * red joker:       17
     */

    QString name() const
    {
        return pattern + QString::number(number);
    }

    bool operator<(const Card& _y) const
    {
        return number < _y.number;
    }

    bool operator>(const Card& _y) const
    {
        return number > _y.number;
    }

//    bool operator==(const Card& _y)
//    {
//        return number == _y.number;
//    }

    friend QDataStream& operator>>(QDataStream& in, Card& _card)
    {
        in >> _card.pattern >> _card.number;
        return in;
    }

    friend QDataStream& operator<<(QDataStream& out, const Card& _card)
    {
        out << _card.pattern << _card.number;
        return out;
    }

};


class DataPackage
{

public:
    int type;
    /* 0:       confirmReady
     * 1:       deal cards
     * 2:       play cards
     */
    int id; // -1: server
    QList<Card> cards;

    DataPackage(const int _id = -1): id(_id)
    {
        type = -1;
        cards.clear();
    }

    void sortCards(std::function<bool (Card, Card)> cmp = std::greater<Card>())
    {
        qSort(cards.begin(), cards.end(), cmp);
    }

    friend QDataStream& operator>>(QDataStream& in, DataPackage& _data)
    {
        in >> _data.type >> _data.id >> _data.cards;
        return in;
    }

    friend QDataStream& operator<<(QDataStream& out, const DataPackage& _data)
    {
        out << _data.type << _data.id << _data.cards;
        return out;
    }
};

class MyTools : public QObject
{
    Q_OBJECT

signals:
    void transferPackage(DataPackage data);

public:
    MyTools();

    template <class T>
    void send(QTcpSocket* socket, const T& data)
    {
        QByteArray bytes;
        QDataStream stream(&bytes, QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_13);
        stream.setByteOrder(QDataStream::BigEndian);
        stream << qint32(0);
        stream << data;
        stream.device()->seek(0);
        // qDebug() << bytes.size() - sizeof(qint32);
        stream << qint32(bytes.size() - sizeof(qint32));
        socket->write(bytes);
        qDebug() << "sent one!";
    }


    void read(QTcpSocket* socket)
    {
        DataPackage data;
        QDataStream in(socket);
        in.setVersion(QDataStream::Qt_5_13);
        in.setByteOrder(QDataStream::BigEndian);
        static qint32 bytesToRead = 0;
        qDebug() << "socket->bytesAvailable(): " << socket->bytesAvailable();
        if (socket->bytesAvailable() < sizeof(qint32))
            return; // the head info of size is incomplete
        while (socket->bytesAvailable())
        {
            if (socket->bytesAvailable() >= sizeof(qint32) && bytesToRead == 0)
                in >> bytesToRead;  // read the size of following data
            qDebug() << "socket->bytesAvailable(): " << socket->bytesAvailable();
            if (socket->bytesAvailable() >= bytesToRead)
            {
                // read data
                qDebug() << "start reading data...";
                char* temp = new char[bytesToRead + 1]{ 0 };
                in.readRawData(temp, bytesToRead);
                qDebug() << "socket->bytesAvailable(): " << socket->bytesAvailable();
                QByteArray buffer(temp, bytesToRead);
                QDataStream stream(&buffer, QIODevice::ReadWrite);
                stream >> data;
                bytesToRead = 0;
                emit transferPackage(data);
            }
           else
                break;  // the data is incomplete; read it next time
        }
    }
};

class CardItem : public QGraphicsPixmapItem
{
    Card card;
public:
    static QMap<QString, CardItem*> map;

    CardItem(const QChar& _pattern, const int _number ):
        card(_pattern, _number)
    {
        setPixmap(":/cards/" + card.name() + ".png");
        //setPos(0, -50);
    }

    CardItem(const Card& _card): card(_card)
    {
        setPixmap(":/cards/" + card.name() + ".png");
        //setPos(0, -50);
    }



};


#endif // MYTOOLS_H
