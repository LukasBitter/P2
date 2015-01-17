#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

#include <QTcpSocket>
#include <QTcpSocket>

class QTcpSocket;

namespace Connexions {
    class Client;
}

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QString host = "localhost", QObject *parent = 0, int port = 0);
    bool isConnexionOk() const;

signals:
    void errorOccured(QAbstractSocket::SocketError socketError);
    void messageReciveFromServeur(QString);

public slots:
    void sendMessageToServer(QString msg);

private slots:
    void readFromSocket();
    void connected();
    void onErrorOccured(QAbstractSocket::SocketError socketError);

private:
    bool connexionOk;
    QDataStream in;
    QTcpSocket *tcpSocket;
};

#endif // CLIENT_H
