#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>

#include <stdlib.h>
#include <process.h>
#include "Connexion/server.h"
#include "GameComponent/map.h"
#include "GameComponent/gamer.h"


#define SEP_CONX "#"
#define SEP_STATUS ";"

Server::Server(QWidget *parent)
:   QDialog(parent), tcpServer(0), networkSession(0)
{
    gameRunning= 0;
    maxPlayers = 4;
    clientsConnectedNb = 0;
    blockSize = 0;
    playerNumber =0;

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewClientRequest()));

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
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        statusLabel->setText(tr("Opening network session."));
        networkSession->open();

    } else {

        sessionOpened();
    }
}

void Server::sessionOpened()
{
    // Save the used configuration
    if (networkSession) {
        QNetworkConfiguration config = networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = config.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen()) {
        QMessageBox::critical(this, tr("Delete Game Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();
        return;
    }

    QString ipAddress;
    ipAddress = getHostIp();


    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();


    statusLabel->setText(tr("The server is running on\n\nIP adresse(s): %1\nport: %2\n\n"
                            "Wait until all players connect and run the Delete Game Client now:")
                         .arg(ipAddress).arg(tcpServer->serverPort()));
}

int Server::getPort()
{
    return tcpServer->serverPort() ;
}

QString Server::getHostIp(){
    qWarning()<<__FUNCTION__;
    QHostInfo hostInfo = QHostInfo::fromName(QHostInfo::localHostName());
    QList<QHostAddress> hostNameLookupAddressList = hostInfo.addresses();
    QList<QHostAddress> interfaceAddressList = QNetworkInterface::allAddresses();
    qDebug()<<__FUNCTION__<<"hostName lookup addresses:"<<hostNameLookupAddressList;
    qDebug()<<__FUNCTION__<<"interface addresses:"<<interfaceAddressList;

    QString hostIpStr;
    foreach(QHostAddress addr, hostNameLookupAddressList){
        if(addr.protocol() == QAbstractSocket::IPv4Protocol && interfaceAddressList.contains(addr)){


            qDebug()<<__FUNCTION__<<addr<<" test";
            if(isLocalIp(addr)){
                qDebug()<<__FUNCTION__<<addr<<" is local ip";
                hostIpStr.append(addr.toString());
                hostIpStr.append(" / ");
                //break;
            }else if(isLinkLocalAddress(addr)){
                qDebug()<<__FUNCTION__<<addr<<" is Link Local Address";
                hostIpStr = addr.toString();
            }
        }
    }
    hostIpStr.remove(hostIpStr.length()-3, 3);

    return hostIpStr;
}

/**
 Link Local address should be in the range
 169.254.1.0 to 169.254.254.255
 Refer :http://en.wikipedia.org/wiki/Private_network
 **/
bool Server::isLinkLocalAddress(QHostAddress addr){
    quint32 hostIpv4Addr = addr.toIPv4Address();
    quint32 rangeMin = QHostAddress("169.254.1.0").toIPv4Address();
    quint32 rangeMax = QHostAddress("169.254.254.255").toIPv4Address();
    if(hostIpv4Addr >= rangeMin && hostIpv4Addr <= rangeMax){
        return true;
    }else{
        return false;
    }
}

/**
  Refer: http://en.wikipedia.org/wiki/Private_network
  Private Ipv4 address ranges:
  1. 10.0.0.0 - 10.255.255.255
  2. 172.16.0.0 - 172.31.255.255
  3. 192.168.0.0 - 192.168.255.255
  */

bool Server::isLocalIp(QHostAddress addr){
    quint32 hostIpv4Addr = addr.toIPv4Address();
    quint32 range1Min = QHostAddress("10.0.0.0").toIPv4Address();
    quint32 range1Max = QHostAddress("10.255.255.255").toIPv4Address();

    quint32 range3Min = QHostAddress("172.16.0.0").toIPv4Address();
    quint32 range3Max = QHostAddress("172.31.255.255").toIPv4Address();

    quint32 range2Min = QHostAddress("192.168.0.0").toIPv4Address();
    quint32 range2Max = QHostAddress("192.168.255.255").toIPv4Address();

    if((hostIpv4Addr >= range1Min && hostIpv4Addr <= range1Max)
            || (hostIpv4Addr >= range2Min && hostIpv4Addr <= range2Max)
            || (hostIpv4Addr >= range3Min && hostIpv4Addr <= range3Max)){
        return true;
    }else{
        return false;
    }
}

void Server::onNewClientRequest()
{
    QString msg;
    //checkPlayersConnected();

    if(clientsConnectedNb < maxPlayers){
        clientsConnectedNb++;

        activeSocket = tcpServer->nextPendingConnection();
        //clientConnections.append(activeSocket);
        connect(activeSocket, SIGNAL(readyRead()), this, SLOT(readRequest()));

        Gamer *g = new Gamer();
        g->setSocket(activeSocket);

        msg = "serverConnectionOk";
        msg.append(SEP_CONX);
        msg.append(QString::number(g->getId()));
        msg.append(SEP_CONX);
        msg.append(Gamer::getLstGamerUpdateString());
        g->setConnected(true);
    }
    else
    {
        clientWaitingList.append(activeSocket);
        msg = "noMoreSocketAvailable";
    }

    qDebug()<<"SERVER: onNewClientRequest / msg =" << msg;

    sendClientResponse(msg);
    endConversation();
}

void Server::endConversation()
{
    activeSocket = NULL;
    //playerNumber = 0;
    blockSize =0;
    qDebug()<<"SERVER: endConversation / END";
}

void Server::readRequest()
{
    //QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    activeSocket = qobject_cast<QTcpSocket*>(sender());

    QDataStream in(activeSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        // we check if first element in DataStream is at least size of a quint16 as expected
        if (activeSocket->bytesAvailable() < (int)sizeof(quint16))
        {
            // if not, readyRead slot will be called another time when new data is available
            qDebug()<<"SERVER: readRequest / activeSocket->bytesAvailable() < (int)sizeof(quint16)";
            return;
        }
        in >> blockSize;
    }

    // we check if the remaining data in datastream is of the expected size
    if (activeSocket->bytesAvailable() < blockSize)
    {
        qDebug()<<"SERVER: readRequest / activeSocket->bytesAvailable() < blockSize";
        return;
    }

    // we catch the rest of the data
    QString clientMessage;
    in >> clientMessage;

    qDebug() << "SERVER: readRequest / clientMessage: " <<clientMessage;

    char *s = new char[activeSocket->bytesAvailable()];
    int n = in.readRawData(s,activeSocket->bytesAvailable());
    //qDebug() << "----------------------------------";
    /*for (int i=0; i <n; i++)
        qDebug() << (int)s[i];*/
    //qDebug() << n;
    //qDebug() << "status :" << in.status();
    //return;

    if(clientMessage != "NOACTION")
    {
        QString rep = parse(clientMessage);
        sendClientResponse(rep);
        if((rep.compare("userNameOK") == 0) || (rep.compare("clientReadyOK") == 0))
            sendAllUsersStatus();
    }
    endConversation();
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

QString Server::parse(QString clientMessage)
{
    QList<QString> listMsg = clientMessage.split(SEP_CONX);
    QString rep = "NOACTION";

    playerNumber = listMsg.at(1).toInt();
    Gamer *g = Gamer::getGamer(playerNumber);

    if(listMsg.at(0) == "ReadyRun")
    {
        if(!gameRunning)
        {
            g->setReady(true);
            rep = "clientReadyOK";
        }
        else
            rep = "gameIsRunning!";
    }
    else if (listMsg.at(0) == "checkUserName")
    {
        if(gameRunning)
            rep = "gameIsRunning!";
        else if(!Gamer::isNameExist(listMsg.at(2)))
        {
            g->setName(listMsg.at(2)); // const?
            rep = "userNameOK";
        }
        else
            rep = "userNameTaken";
    }
    else if (listMsg.at(0) == "clientClose")
    {
        // delete gamer
        activeSocket->disconnectFromHost();
        qDebug() << "Host disconnected";

    }
    else if (listMsg.at(0) == "runGame")
    {
        //createGamers(); // pas besoin car déjà créés
        buildMap();
        for (int i=0; i < maxPlayers; i++)
        {
            sendClientResponse("lauchGame");
        }
    }
    else
        rep = "NO PLANNED ACTION FOR";

    return rep;
}

void Server::buildMap()
{
    //Création de la map

    Map *m = new Map(0);
    Node *campsBaseNils = new Node(180,-150,50,100,nils,0);
    Node *campsBaseLukas = new Node(-0,-200,30,100,lukas,0);
    Node *aventageNils = new Node(180,10,10,10,0,0);
    Node *lienLukasNils = new Node(-10,-20,50,110,0,0);

    campsBaseNils->setRessourcesRate(1);
    campsBaseLukas->setRessourcesRate(1);
    aventageNils->setRessourcesRate(1);
    lienLukasNils->setRessourcesRate(1);

    campsBaseNils->setNbRessources(50);
    campsBaseLukas->setNbRessources(50);
    lienLukasNils->setNbRessources(50);

    m.addNode(*campsBaseNils);
    m.addNode(*campsBaseLukas);
    m.addNode(*aventageNils);
    m.addNode(*lienLukasNils);
    m.addConnexion(*lienLukasNils, *campsBaseNils);
    m.addConnexion(*lienLukasNils, *campsBaseLukas);
    m.addConnexion(*aventageNils, *campsBaseNils);
    m.addConnexion(*campsBaseNils, *campsBaseLukas);
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
