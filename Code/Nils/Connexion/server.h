#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include <QTcpSocket>

class QTcpServer;
class QTcpSocket;

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
    void errorOccured(QTcpSocket::SocketError socketError);
    void messageReciveFromClient(QTcpSocket *t, QString msg);

public slots:
    void sendMessageToClient(QTcpSocket *socket, QString msg);
    void onErrorOccured(QTcpSocket::SocketError socketError);
private slots:
    void readFromSocket();
    void onNewClient();

private:
    bool connexionOk;
    QTcpServer *tcpServer;

signals:
};

#endif // SERVER_H
