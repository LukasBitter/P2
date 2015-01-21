#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>
#include <QStringBuilder>

#include "GameConnexion/client.h"
#include "gamer.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Client::Client(int port, QString host, QObject *parent) : QObject(parent),
    blockSize(0)
{
    connect(&socket, SIGNAL(readyRead()), this, SLOT(readFromSocket()));
    connect(&socket, SIGNAL(connected()), this, SLOT(afterConnexion()));
    connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onErrorOccured(QAbstractSocket::SocketError)));

    socket.connectToHost(host,port);
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void Client::onErrorOccured(QAbstractSocket::SocketError socketError)
{
    qWarning()<<"Client : enter 'onErrorOccured'"<<socketError;

    emit errorOccured(socketError);
}

void Client::sendMessageToServer(QString msg)
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

void Client::readFromSocket()
{
    QDataStream in(&socket);
    in.setVersion(QDataStream::Qt_4_0);

    while(socket.bytesAvailable() > 0)
    {
        if (blockSize == 0)
        {
            if (socket.bytesAvailable() < (int)sizeof(quint16))
                return;
            in >> blockSize;
        }

        if (socket.bytesAvailable() < blockSize)
            return;

        QString serverMessage;
        in >> serverMessage;

        blockSize = 0;
        emit messageReciveFromServeur(serverMessage);
    }
}

void Client::afterConnexion()
{
    qDebug()<<"Client : successfull connexion to server";

    emit connected();
}

