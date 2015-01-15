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

signals:
    void errorOccured(QAbstractSocket::SocketError socketError);
    void messageRecive(QString);

private slots:
    void readFromSocket();
    void onErrorOccured(QAbstractSocket::SocketError socketError);
    void onNewClient();

private:
    bool connexionOk;
    QList<QTcpSocket *> lstClient;
    QTcpServer *tcpServer;
    QTcpSocket *activeSocket;
    QDataStream in;
    QByteArray block;
    quint16 blockSize;

    /*METHODE PRIVE*/
    void sendClientResponse(QString ConnectionMsg);
    bool checkAvailableSocket();
    QString parse(QString clientMessage);
    void sendAllUsersStatus();
    void endConversation();
    void checkPlayersConnected();
    bool isLinkLocalAddress(QHostAddress addr);
    bool isLocalIp(QHostAddress addr);

signals:
};

#endif // SERVER_H
