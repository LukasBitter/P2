#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

#include <QTcpSocket>

class QTcpSocket;

namespace Connexions {
    class Client;
}

class Client : QObject
{
    Q_OBJECT
public:
    explicit Client(QString host = "localhost", QObject *parent = 0, int port = 0);
    bool isConnexionOk() const;

signals:
    void errorOccured(QAbstractSocket::SocketError socketError);
    void messageRecive(QString);

public slots:
    void sendServerMessage(QString msg);

private slots:
    void readFromSocket();
    void onErrorOccured(QAbstractSocket::SocketError socketError);

private:
    bool connexionOk;
    QDataStream in;
    QTcpSocket *tcpSocket;
    quint16 blockSize;
    QNetworkSession *networkSession;
};

#endif // CLIENT_H
