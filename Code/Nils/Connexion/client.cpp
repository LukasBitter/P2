#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>
#include <QStringBuilder>

#include "Connexion/client.h"
#include "GameComponent/map.h"
#include "GameComponent/gamer.h"

#define SEP_CONX "#"
#define SEP_STATUS ";"

Client::Client(QString host, QObject *parent, int port) : QObject(parent),
    connexionOk(false), blockSize(0), networkSession(0)
{
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readFromSocket()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onErrorOccured(QAbstractSocket::SocketError)));

    tcpSocket->connectToHost(host,port);
    if(tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        connexionOk = true;
    }
}

void Client::onErrorOccured(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug()<<"Erreur 1";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug()<<"Erreur 2";
        break;
    default:
        qDebug()<<"Erreur default";
    }
    emit errorOccured(socketError);
}

void Client::sendServerMessage(QString msg)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)0;
    out << msg;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    qDebug()<<"CLIENT: sendServerMessage / msg: "<<msg;

    tcpSocket->write(block);
    tcpSocket->flush();
}

void Client::readFromSocket()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0)
    {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }

    if (tcpSocket->bytesAvailable() < blockSize)
        return;

    QString serverMessage;
    in >> serverMessage;

    blockSize = 0;
    emit messageRecive(serverMessage);
}

bool Client::isConnexionOk() const
{
    return connexionOk;
}
