#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

#include <QTcpSocket>
#include <QTcpSocket>

class QTcpSocket;

namespace GameConnexion {
    class Client;
}

class Client : public QObject
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit Client(int port = 0, QString host = "localhost", QObject *parent = 0);

    /*SIGNALS/SLOTS*/
signals:
    void errorOccured(QAbstractSocket::SocketError socketError);
    void messageReciveFromServeur(QString);
    void connected();
public slots:
    void sendMessageToServer(QString msg);
private slots:
    void readFromSocket();
    void afterConnexion();
    void onErrorOccured(QAbstractSocket::SocketError socketError);

private:
    /*OUTIL*/
    QDataStream in;
    QTcpSocket socket;
    quint16 blockSize;
};

#endif // CLIENT_H
