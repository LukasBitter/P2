#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QAbstractSocket>

class QTcpServer;
class QTcpSocket;

namespace GameConnexion {
class Server;
}

class Server : public QObject
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit Server(int port, int maxConnexion, QObject *parent = 0);

    /*ASSESSEUR / MUTATEUR*/
    bool isConnexionOk() const;

    /*SIGNALS/SLOTS*/
signals:
    void errorOccured(QAbstractSocket::SocketError socketError);
    void messageReciveFromClient(QTcpSocket *t, QString msg);

public slots:
    void sendMessageToClient(QTcpSocket *socket, QString msg);
private slots:
    void onErrorOccured(QAbstractSocket::SocketError socketError);
    void readFromSocket();
    void onNewClient();

private:
    /*OUTIL*/
    QTcpServer *tcpServer;

    /*SORTIE*/
    bool connexionOk;
};

#endif // SERVER_H
