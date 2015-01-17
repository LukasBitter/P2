#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>
#include <QStringBuilder>

#include "GameConnexion/client.h"
#include "GameComponent/map.h"
#include "GameComponent/gamer.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Client::Client(int port, QString host, QObject *parent) : QObject(parent),
    connexionOk(false)
{
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readFromSocket()));
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(afrterConnexion()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onErrorOccured(QAbstractSocket::SocketError)));

    tcpSocket->connectToHost(host,port);
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

bool Client::isConnexionOk() const
{
    return connexionOk;
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

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

void Client::sendMessageToServer(QString msg)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)(block.size() - sizeof(quint16));
    out << msg;

    qDebug()<<"CLIENT: sendServerMessage / msg: "<<msg;

    tcpSocket->write(block);
    tcpSocket->flush();
}

void Client::readFromSocket()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    quint16 blockSize = 0;
    if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
        return;
    in >> blockSize;

    QString serverMessage;
    in >> serverMessage;

    blockSize = 0;
    emit messageReciveFromServeur(serverMessage);
}

void Client::afrterConnexion()
{
    connexionOk = true;
    emit connected();
}

