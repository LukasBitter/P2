#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include <QTcpSocket>

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
    explicit Server(int port, int maxConnexion, QWidget *parent = 0);

    /*ASSESSEUR / MUTATEUR*/
    bool isConnexionOk() const;

    /*SIGNALS/SLOTS*/
signals:
    void errorOccured(QTcpSocket::SocketError socketError);
    void messageReciveFromClient(QTcpSocket *t, QString msg);

public slots:
    void sendMessageToClient(QTcpSocket *socket, QString msg);
    void onErrorOccured(QTcpSocket::SocketError socketError);
private slots:
    void readFromSocket();
    void onNewClient();

private:
    /*OUTIL*/
    QTcpServer *tcpServer;

    /*SORTIE*/
    bool connexionOk;
};

#endif // SERVER_H
