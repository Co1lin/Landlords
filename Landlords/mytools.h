#ifndef MYTOOLS_H
#define MYTOOLS_H

#include <QtNetwork>
#include <QGraphicsItem>
#include <QtMath>


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

    bool operator==(const Card& _y) const
    {
        return number == _y.number;
    }

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

class PlayerInfo : public QGraphicsTextItem
{
public:
    int id;
    int cardsRemain;
    QString role;
    QString note;

    PlayerInfo()
    {
        id = -1;
        cardsRemain = -1;
        role = "null";
    }

    QString content()
    {
        return "<p><span style=\"color:#FFC0CB;\">玩家ID：" + QString::number(id) + " " + note + "</span>" +
                "<br><span style=\"color:#FFFF00;\">剩余牌数： " + QString::number(cardsRemain) + "</span>" +
                "<br><span style=\"color:#E53333;\">角色： " + role + "</span></p>";
    }

    PlayerInfo(const int _id, const int _cardsRemain, const QString& _role):
        id(_id), cardsRemain(_cardsRemain), role(_role)
    {
        setHtml(content());
    }

    PlayerInfo(const PlayerInfo& _playerInfo)
    {
        id = _playerInfo.id;
        cardsRemain = _playerInfo.cardsRemain;
        role = _playerInfo.role;
        setHtml(content());
    }

    void setNote(const QString &_note)
    {
        note = _note;
        setHtml(content());
    }

    PlayerInfo& operator=(const PlayerInfo& _playerInfo)
    {
        id = _playerInfo.id;
        cardsRemain = _playerInfo.cardsRemain;
        role = _playerInfo.role;
        setHtml(content());
        return *this;
    }

    friend QDataStream& operator>>(QDataStream& in, PlayerInfo& _data)
    {
        in >> _data.id >> _data.cardsRemain >> _data.role;
        _data.setHtml(_data.content());
        return in;
    }

    friend QDataStream& operator<<(QDataStream& out, const PlayerInfo& _data)
    {
        out << _data.id << _data.cardsRemain << _data.role;
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
     * 3:       decide the landlord
     */
    int id; // -1: server
    QList<Card> cards;
    QVector<QString> msg;
    QVector<PlayerInfo> playerInfo;

    DataPackage(const int _id = -1): id(_id)
    {
        type = -1;
        cards.clear();
        for (int i = 0; i <= 2; i++)
            playerInfo.push_back(PlayerInfo(-1, -1, "null"));
    }

    void sortCards(std::function<bool (Card, Card)> cmp = std::greater<Card>())
    {
        std::sort(cards.begin(), cards.end(), cmp);
    }

    friend QDataStream& operator>>(QDataStream& in, DataPackage& _data)
    {
        in >> _data.type >> _data.id >> _data.cards >> _data.msg >> _data.playerInfo;
        return in;
    }

    friend QDataStream& operator<<(QDataStream& out, const DataPackage& _data)
    {
        out << _data.type << _data.id << _data.cards << _data.msg << _data.playerInfo;
        return out;
    }
};

class MyTools : public QObject
{
    Q_OBJECT

signals:
    void transferPackage(DataPackage data);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override
    {
        if (event->type() == QEvent::GraphicsSceneMousePress)
        {
            qDebug() << "event filtered";
            return true;
        }
        else
            return QObject::eventFilter(watched, event);
    }

public:
    MyTools();

    static QVector<QString> getLocalIP()
    {
        QVector<QString> ipv4, ipv6;
        QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
        foreach (auto addr, info.addresses())
        {
            if (addr.protocol() == QAbstractSocket::IPv4Protocol)
                ipv4 << addr.toString();
            else if (addr.protocol() == QAbstractSocket::IPv6Protocol)
                ipv6 << addr.toString();
        }
        ipv4 << ipv6;
        return ipv4;
    }

    static QString getLocalIPString()
    {
        QString ipInfo;
        auto ipVec = getLocalIP();
        foreach (auto& ip, ipVec)
        {
            ipInfo += ip;
            ipInfo += "\n";
        }
        return ipInfo;
    }

    static int nextId(const int _id)
    {
        return (_id + 1) % 3;
    }

    template <class T>
    static void sortCards(T& cards, std::function<bool (Card, Card)> cmp = std::greater<Card>())
    {
        std::sort(cards.begin(), cards.end(), cmp);
    }

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
        //qDebug() << "socket->bytesAvailable(): " << socket->bytesAvailable();
        if (socket->bytesAvailable() < sizeof(qint32))
            return; // the head info of size is incomplete
        while (socket->bytesAvailable())
        {
            if (socket->bytesAvailable() >= sizeof(qint32) && bytesToRead == 0)
                in >> bytesToRead;  // read the size of following data
            //qDebug() << "socket->bytesAvailable(): " << socket->bytesAvailable();
            if (socket->bytesAvailable() >= bytesToRead)
            {
                // read data
                //qDebug() << "start reading data...";
                char* temp = new char[bytesToRead + 1]{ 0 };
                in.readRawData(temp, bytesToRead);
                //qDebug() << "socket->bytesAvailable(): " << socket->bytesAvailable();
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

    template <class T>
    void installMyEventFilter(T* _obj)
    {
        _obj->installEventFilter(this);
    }

    static QMap<int, int> makeMap(const QList<Card>& cards)
    {
        QMap<int, int> map;
        foreach (auto card, cards)
        {
            auto iter = map.find(card.number);
            if (iter == map.end())
                map[card.number] = 1;
            else
                map[card.number]++;
        }
        return map;
    }

    static QPair<int, int> maxSame(const QList<Card>& cards)
    {
        // return (cardNumber, maxCount)
        auto map = makeMap(cards);
        int number = 0;
        int result = 0;
        for (auto iter = map.begin(); iter != map.end(); iter++)
        {
            if (result < iter.value())
            {
                result = iter.value();
                number = iter.key();
            }
        }
        return QPair(number, result);
    }

    static QPair<int, int> hasStraignt(QList<Card> cards)
    {
        // return (start, end)
        sortCards(cards);
        int start = cards.last().number, end = cards.first().number;
        int i = 0;
        for (auto iter = cards.rbegin(); iter != cards.rend(); iter++)
        {
            if (iter->number == start + i)
                i++;
            else
                return QPair(-1, -1);
        }
        if (3 <= start && end <= 14)
            return QPair(start, end);
        return QPair(start, end);
    }

    static QPair<int, int> hasStraignt(QList<int> cards)
    {
        // return (start, end)
        std::sort(cards.begin(), cards.end(), std::greater<int>());
        int start = cards.last(), end = cards.first();
        int i = 0;
        for (auto iter = cards.rbegin(); iter != cards.rend(); iter++)
        {
            if (*iter == start + i)
                i++;
            else
                return QPair(-1, -1);
        }
        if (3 <= start && end <= 14)
            return QPair(start, end);
        else
            return QPair(-1, -1);
    }
};

class CardItem : public QGraphicsPixmapItem
{
    Card card;
    bool selected;

    void construct()
    {
        selected = false;
        setPixmap(":/cards/" + card.name() + ".png");
        //this->setAcceptedMouseButtons(Qt::LeftButton);
        //setFlag(QGraphicsItem::ItemIsSelectable);
    }

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override
    {
        if (!selected)
            setPos(pos().x(), pos().y() - 50);
        else
            setPos(pos().x(), pos().y() + 50);
        selected = !selected;
    }

public:

    CardItem(const QChar& _pattern, const int _number ):
        card(_pattern, _number)
    {
        construct();
    }

    CardItem(const Card& _card): card(_card)
    {
        construct();
    }

    bool isSelected()
    {
        return this->selected;
    }

    Card getCard() const
    {
        return card;
    }
};

#endif // MYTOOLS_H
