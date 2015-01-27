#ifndef SERVER_H
#define SERVER_H

#include "global.h"

namespace GameConnexion
{
    class Server;
}

/**
 * @class Server
 * @brief Permet l'envoit de texte aux clients et répertorie les clients connectés
 */
class Server : public QObject
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit Server(int port, int maxConnexion, QObject *parent = 0);

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
    QTcpServer tcpServer;
    QHash<QTcpSocket*, quint16> blockSizeArray;
};

#endif // SERVER_H
