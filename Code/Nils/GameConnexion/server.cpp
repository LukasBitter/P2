#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>

#include <stdlib.h>
#include <process.h>
#include "GameConnexion/server.h"
#include "GameComponent/map.h"
#include "GameComponent/gamer.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Server::Server(int port, int maxConnexion, QWidget *parent) :
    QObject(parent), tcpServer(0)
{
    tcpServer = new QTcpServer(this);

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewClient()));

    tcpServer->setMaxPendingConnections(maxConnexion);
    tcpServer->listen(QHostAddress::Any, port);
    if(tcpServer->isListening())
    {
        connexionOk = true;
    }
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

bool Server::isConnexionOk() const
{
    return connexionOk;
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void Server::onNewClient()
{
    QTcpSocket *activeSocket = tcpServer->nextPendingConnection();

    connect(activeSocket, SIGNAL(readyRead()), this, SLOT(readFromSocket()));
    connect(activeSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onErrorOccured(QAbstractSocket::SocketError)));
}

void Server::readFromSocket()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_0);

    quint16 blockSize = 0;
    if (socket->bytesAvailable() < (int)sizeof(quint16))
        return;
    in >> blockSize;

    QString clientMessage;
    in >> clientMessage;

    blockSize = 0;
    emit messageReciveFromClient(socket, clientMessage);
}

void Server::onErrorOccured(QAbstractSocket::SocketError socketError)
{
    emit errorOccured(socketError);
}

void Server::sendMessageToClient(QTcpSocket *socket, QString msg)
{
    if(socket != 0)
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_0);

        out << (quint16)(block.size() - sizeof(quint16));
        out << msg;

        qDebug()<<"SERVER: buildClientResponse / msg: "<<msg;

        socket->write(block);
        socket->flush();
    }
}
