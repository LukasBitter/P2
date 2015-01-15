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
    playerNumber(0), userName(""), port(port), host(host),
    connexionOk(false), nameOk(false), readyOk(false), blockSize(0),
    networkSession(0), isHost(isHost)
{
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readServerResponse()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onErrorOccured(QAbstractSocket::SocketError)));

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        //connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        //statusLabel->setText(tr("Opening network session."));
        emit setStatusLabel(tr("Opening network session."));
        networkSession->open();
    }
}

void Client::requestNewConnection()
{
    if(userNameLineEdit->text().isEmpty())
    {
        setStatus("Insert your name");
        return;
    }

    if(playerNumber == "NULL")
    {
        qDebug()<<"CLIENT: requestNewConnection";
        blockSize = 0;

        tcpSocket->abort();
        tcpSocket->connectToHost(hostCombo->currentText(),
                                 portLineEdit->text().toInt());
    }
    else
    {
        QString rep = buildStringCheckUserName();
        sendServerMessage(rep);
        getConnectionButton->setText(tr("Connection"));
    }

    getConnectionButton->setEnabled(false);
}

void Client::onErrorOccured(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Delete Game Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Delete Game Client"),
                                 tr("The Connection was refused by the peer. "
                                    "Make sure the Delete Game server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Delete Game Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
    }

}



//void Client::sessionOpened()
//{
//    // Save the used configuration
//    QNetworkConfiguration config = networkSession->configuration();
//    QString id;
//    if (config.type() == QNetworkConfiguration::UserChoice)
//        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
//    else
//        id = config.identifier();

//    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
//    settings.beginGroup(QLatin1String("QtNetwork"));
//    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
//    settings.endGroup();

//    statusLabel->setText(tr("This client requires that you run the "
//                            " Delete Game Server example as well."));

//    enableGetConnectionButton();
//}

void Client::runGame()
{
    QString msg = "runGame";
    sendServerMessage(msg);

}

void Client::launchGame()
{
    Gamer *g = new Gamer(playerNumber);
    game = new Map(g);
    //this->hide();
    game->show();
}

void Client::ReadyRun()
{
    qDebug()<<"CLIENT: ReadyRun / tcpSocket->state() / 1: "<<tcpSocket->state();
    blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    qDebug()<<"CLIENT: ReadyRun / block.size() before: "<<block.size();

    QString sReadyRun("ReadyRun");
    sReadyRun.append(SEP_CONX);
    sReadyRun.append(playerNumber);
    //QString tNumber = "1";

    out << (quint16)0;
    out << sReadyRun;
    //out << tNumber;
    out << playerNumber;
    out.device()->seek(0);

    qDebug()<<"CLIENT: ReadyRun / block.size() after: "<<block.size();
    out << (quint16)(block.size() - sizeof(quint16));

    qDebug()<<"CLIENT: ReadyRun / String: "<<sReadyRun;
    qDebug()<<"CLIENT: ReadyRun / playerNumber: "<<playerNumber;

    tcpSocket->write(block);
    tcpSocket->flush();


}

void Client::sendServerMessage(QString msg)
{
    QString str = pla
    qDebug()<<"CLIENT: sendServerMessage";
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

void Client::readServerResponse()
{
    qDebug()<<"CLIENT: readServerResponse ";
    //QTcpSocket *localTcpSocket = (QTcpSocket*)sender();
    QDataStream in(tcpSocket);
    //in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    qDebug()<<"CLIENT: readServerResponse / blockSize before: " << blockSize;
    qDebug()<<"CLIENT: readServerResponse / tcpSocket: " << tcpSocket->state();

     while ( tcpSocket->bytesAvailable() >0 )
     {
         if (blockSize == 0) {
            if (tcpSocket->bytesAvailable() < (int)sizeof(quint16)){
                qDebug()<<"CLIENT: readServerResponse / bytesAvailable() < (int)sizeof(quint16)";
                return;
            }

            in >> blockSize;
            qDebug()<<"CLIENT: readServerResponse / blockSize after: " << blockSize;
            if(blockSize == 0)
            {
                in >> blockSize;
                qDebug()<<"CLIENT: readServerResponse / blockSize after: " << blockSize;
            }
         }
        qDebug()<<"CLIENT: readServerResponse / tcpSocket->bytesAvailable(): " << tcpSocket->bytesAvailable();

        if (tcpSocket->bytesAvailable() < blockSize)
        {
            qDebug()<<"CLIENT: readServerResponse / bytesAvailable() < blockSize";
            //return;
        }

        QString serverMessage;
        in >> serverMessage;

        qDebug()<<"CLIENT: readServerResponse / serverHeader: "<<serverMessage;

        QString rep = parse(serverMessage);

        blockSize = 0;

        if(rep.compare("NOACTION") != 0)
        {
            sendServerMessage(rep);
        }

//        if(rep.compare("NOACTIONN") != 0)
//        {
//            QByteArray block;
//            QDataStream out(&block, QIODevice::WriteOnly);
//            out.setVersion(QDataStream::Qt_4_0);

//            out << (quint16)0;
//            out << rep;
//            out.device()->seek(0);
//            out << (quint16)(block.size() - sizeof(quint16));

//            qDebug()<<"CLIENT: readServerResponse / headerOut: "<<headerOut;
//            qDebug()<<"CLIENT: readServerResponse / msg: "<<rep;

//            tcpSocket->write(block);
//            tcpSocket->flush();
//        }
//        else

//            qDebug()<<"CLIENT: readServerResponse / NOACTION";
     }
     qDebug()<<"CLIENT: readServerResponse / END WHILE";
     endConversation();
}

void Client::endConversation()
{
    qDebug() << "END CONVERSATION";
    blockSize =0;
    updateScreen();
}

QString Client::parse(QString serverMessage)
{
    QList<QString> listMsg = serverMessage.split(SEP_CONX);
    QString rep = "NOACTION";

    if (listMsg.at(0) == "serverConnectionOk")
    {
        qDebug()<<"CLIENT: parse / setPlayerId";
        playerNumber = listMsg.at(1);
        emit updateStatus(2));
        //setStatus("Connected to server. Checking user name");
        rep = buildStringCheckUserName();
        //setUsersStatus(listMsg.at(2));
        Gamer::updateLstGamerFromString(listMsg.at(2));
    }
    else if (listMsg.at(0) == "allUsersStatus")
    {
        setUsersStatus(listMsg.at(1));
    }
    else if (listMsg.at(0) == "userNameOK")
    {
        emit userNameOk();
    }
    else if (listMsg.at(0) == "userNameTaken")
    {
        emit userNameTaken();
    }
    else if (listMsg.at(0) == "lauchGame")
    {
        qDebug() << "client lauchgame " << playerNumber;
    }
    else if (listMsg.at(0) == "noMoreSocketAvailable" )
        setStatus("game full!");
    else if (listMsg.at(0) == "clientReadyOK" )
        setStatus("Ready for game to begin. Wait for server to start game");
    else if (listMsg.at(0) == "OK" )
        // do nothing
        ;
    else
    {
        qDebug() << "could not read";
        setStatus("could not read server header");
    }

    return rep;
}

QString Client::buildStringCheckUserName()
{
    QString rep = "checkUserName";
    rep.append(SEP_CONX);
    rep.append(playerNumber);
    rep.append(SEP_CONX);
    rep.append(userNameLineEdit->text());

    return rep;
}

void Client ::setUsersStatus(QString msg)
{
    qDebug()<<"CLIENT: setUsersStatus";

    Gamer::updateLstGamerFromString(msg);
//    QList<QString> listStatus = msg.split(SEP_STATUS);

//    for(int i = 0; i<4;i++)
//    {
//        lPlayersNumbers.at(i)->setText(listStatus.at(i));
//        lPlayersNames.at(i)->setText(listStatus.at(i+1*maxPlayers));
//        lPlayersConnected.at(i)->setText(listStatus.at(i+2*maxPlayers));
//        lPlayersReady.at(i)->setText(listStatus.at(i+3*maxPlayers));
//    }
}

void Client::closeEvent( QCloseEvent *e) {

    QString rep = "clientClose";
    rep.append(SEP_CONX);
    rep.append(playerNumber);
    sendServerMessage(rep);
    e->accept();
}



/*----------------------------------------------------*/
/*ASSESSEUR /
/*----------------------------------------------------*/

int Client::getMaxPlayers() const
{
    return maxPlayers;
}

QString *Client::getUserName() const
{
    return userName;
}

QString Client::getPort() const
{
    return port;
}

/*----------------------------------------------------*/
/* MUTATEUR*/
/*----------------------------------------------------*/

void Client::setUserName(QString *name)
{
    userName = name;
}

bool Client::isConnexionOk() const
{
    return connexionOk;
}

bool Client::isNameOk() const
{
    return nameOk;
}

bool Client::isReadyOk() const
{
    return readyOk;
}

void Client::setReady(bool r)
{
    readyOk = r;
}
