#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>

#include <stdlib.h>
#include <process.h>
#include "Connexion/server.h"
#include "GameComponent/map.h"
#include "GameComponent/gamer.h"


Server::Server(int port, int maxConnexion, QWidget *parent) :
    QObject(parent), tcpServer(0), networkSession(0), blockSize(0)
{
    this->maxConnexion = maxConnexion;
    tcpServer = new QTcpServer(this);

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewClient()));

    tcpServer->setMaxPendingConnections(maxConnexion);
    tcpServer->listen();
    if(tcpServer->isListening())
    {
        connexionOk = true;
    }
}

void Server::onNewClient()
{
    activeSocket = tcpServer->nextPendingConnection();

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readFromSocket()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onErrorOccured(QAbstractSocket::SocketError)));
}

void Client::readFromSocket()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }

    if (socket->bytesAvailable() < blockSize)
        return;

    QString clientMessage;
    in >> clientMessage;

    blockSize = 0;
    emit messageReciveFromServeur(clientMessage);
}

void Server::sendAllUsersStatus()
{
    foreach(Gamer *ele, Gamer::getLstGamer())
    //if(lPlayersConnected.at(i)->text().compare("Connected") == 0)
    {
        activeSocket = ele->getSocket();
        //activeSocket = clientConnections.at(i);

        QString msg = "allUsersStatus";
        msg.append(SEP_CONX);
        msg.append(Gamer::getLstGamerUpdateString());

        sendClientResponse(msg);
    }
}

void Server::sendClientResponse(QString msg)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    qDebug()<<"SERVER: buildClientResponse / msg: "<<msg;

    out << (quint16)0;
    out << msg;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    QString w = QString::number(activeSocket->write(block));
    qDebug() << "w: " << w;
    activeSocket->flush();
}
