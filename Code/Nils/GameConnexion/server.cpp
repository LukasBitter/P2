#include <QtWidgets>
#include <QDebug>

#include <stdlib.h>
#include <process.h>
#include "GameConnexion/server.h"
#include "gamer.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Server::Server(int port, int maxConnexion, QObject *parent) :
    QObject(parent)
{
    connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(onNewClient()));

    tcpServer.setMaxPendingConnections(maxConnexion);
    tcpServer.listen(QHostAddress::Any, port);
    if(tcpServer.isListening())
    {
        qDebug()<<"Server : is listening port";
    }
    else
    {
        qCritical()<<"Server : is NOT listening port";
    }
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void Server::onNewClient()
{
    qDebug()<<"Server : new client has joint the server";
    QTcpSocket *activeSocket = tcpServer.nextPendingConnection();

    blockSizeArray.insert(activeSocket, 0);

    connect(activeSocket, SIGNAL(readyRead()), this, SLOT(readFromSocket()));
    connect(activeSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onErrorOccured(QAbstractSocket::SocketError)));
}

void Server::readFromSocket()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    quint16 blockSize = blockSizeArray.value(socket);
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_0);

    while(socket->bytesAvailable() > 0)
    {
        if (blockSize == 0)
        {
            if (socket->bytesAvailable() < (int)sizeof(quint16))
                break;
            in >> blockSize;
        }

        if (socket->bytesAvailable() < blockSize)
            break;

        QString clientMessage;
        in >> clientMessage;

        blockSize = 0;
        emit messageReciveFromClient(*socket, clientMessage);
    }
    blockSizeArray.insert(socket,blockSize);
}

void Server::onErrorOccured(QAbstractSocket::SocketError socketError)
{
    qWarning()<<"Server : enter 'onErrorOccured'"<<socketError;
    emit errorOccured(socketError);
}

void Server::sendMessageToClient(QTcpSocket &socket, QString &msg)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)0;
    out << msg;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    socket.write(block);
    socket.flush();
}
