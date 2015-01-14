#ifndef SERVER_H
#define SERVER_H

#include <QDialog>

class QLabel;
class QPushButton;
class QTcpServer;
class QTcpSocket;
class QNetworkSession;
class QDataStream;
class QHostAddress;
class Gamer;

namespace Connexions {
class Server;
}

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    int getPort();

private slots:
    void sessionOpened();
    void onNewClientRequest();
    void readRequest();

private:
    QLabel *statusLabel;
    QList<QTcpSocket *> clientConnections;
    QList<QTcpSocket *> clientWaitingList;
    QTcpServer *tcpServer;
    QTcpSocket *activeSocket;
    QDataStream in;
    QNetworkSession *networkSession;
    QByteArray block;
    quint16 blockSize;
    Gamer *currentGamer;
    int playerNumber;
    bool gameRunning;
    int clientsConnectedNb;
    int playersInGame;
    int maxPlayers;

    /*METHODE PRIVE*/
    void sendClientResponse(QString ConnectionMsg);
    bool checkAvailableSocket();
    QString parse(QString clientMessage);
    void sendAllUsersStatus();
    void endConversation();
    void checkPlayersConnected();
    QString getHostIp();
    bool isLinkLocalAddress(QHostAddress addr);
    bool isLocalIp(QHostAddress addr);
    void buildMap();

signals:
};

#endif // SERVER_H
