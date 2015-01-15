#ifndef SERVER_H
#define SERVER_H

#include <QObject>

class QTcpServer;
class QTcpSocket;
class QDataStream;
class QHostAddress;

namespace Connexions {
class Server;
}

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(int port, int maxConnexion, QWidget *parent = 0);
    bool isConnexionOk() const;

private slots:
    void sessionOpened();
    void onNewClientRequest();
    void readRequest();

private:
    bool connexionOk;
    QList<QTcpSocket *> clientConnections;
    QList<QTcpSocket *> clientWaitingList;
    QTcpServer *tcpServer;
    QTcpSocket *activeSocket;
    QDataStream in;
    QNetworkSession *networkSession;
    QByteArray block;
    quint16 blockSize;
    int maxConnexion;

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

signals:
};

#endif // SERVER_H
