#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

enum Status {empty, connected, ready};
class QTcpSocket;

class Player : public QObject
{
    Q_OBJECT

    QTcpSocket *playerId;
    Status playerStatus;
    QString playerName;
    int playerNumber;
    int playerPts;
    int count;

public:
    explicit Player(QObject *parent = 0);
    Player(int num, int pts);
    void addPoint();
    void removePoint();
    int getPoints();
    QString getPlayerName();
    void setPlayerName(QString name);
    QString addCount();

signals:

public slots:

};

#endif // PLAYER_H
