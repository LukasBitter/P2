#ifndef CLIENT_H
#define CLIENT_H

#include "global.h"

class QTcpSocket;

namespace GameConnexion
{
    class Client;
}

/**
 * @class Client
 * @brief Permet l'envoit de texte au server
 */
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
