#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>

#include <stdlib.h>
#include "server.h"
#include <process.h>

Server::Server(QWidget *parent)
:   QDialog(parent), tcpServer(0), networkSession(0)
{
    statusLabel = new QLabel;
    quitButton = new QPushButton(tr("Quit"));
    runButton = new QPushButton(tr("Run"));
    quitButton->setAutoDefault(false);
    runButton->setAutoDefault(false);
    maxPts = 20;
    maxPlayers = 4;
    clientMessage = "";
    playerNumber =0;

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

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewClientRequest()));

    init();
    setUI();

    setWindowTitle(tr("Delete Game Server"));

}

void Server::init(){
    for(int i= 0; i<maxPlayers;i++)
    {
        listPlayers.append(new Player(i, maxPts));
        lPlayersNumbers.append(new QLabel(QString("#").append(QString::number(i+1))));
        lPlayersConnected.append(new QLabel("n/a"));
        lPlayersReady.append(new QLabel(""));
    }
    playersInGame = 0;
    clientsConnectedNb = 0;
    blockSize = 0;

    lPlayerH = new QLabel(tr("Player: "));
    lPlayersConnectedH = new QLabel(tr("Connexion: "));
    lPlayersReadyH = new QLabel(tr("Ready: "));
    gameRunning= 0;
}

void Server::setUI()
{
    QGridLayout *gridLayout= new QGridLayout(this);
    gridLayout->setColumnStretch(1, 40);
    gridLayout->setColumnStretch(2, 25);
    gridLayout->setColumnStretch(3, 35);
    gridLayout->setColumnStretch(4, 35);
    gridLayout->setColumnStretch(5, 35);

    gridLayout->setRowStretch(1,20);
    gridLayout->setRowStretch(2,10);
    gridLayout->setRowStretch(3,10);
    gridLayout->setRowStretch(4,10);
    gridLayout->setRowStretch(5,10);

    gridLayout->addWidget(statusLabel,1, 1, 1, 4);
    gridLayout->addWidget(lPlayerH,2, 1);
    gridLayout->addWidget(lPlayersNumbers.at(0),2, 2);
    gridLayout->addWidget(lPlayersNumbers.at(1),2, 3);
    gridLayout->addWidget(lPlayersNumbers.at(2),2, 4);
    gridLayout->addWidget(lPlayersNumbers.at(3),2, 5);
    gridLayout->addWidget(lPlayersConnectedH,3, 1);
    gridLayout->addWidget(lPlayersConnected.at(0),3, 2);
    gridLayout->addWidget(lPlayersConnected.at(1),3, 3);
    gridLayout->addWidget(lPlayersConnected.at(2),3, 4);
    gridLayout->addWidget(lPlayersConnected.at(3),3, 5);
    gridLayout->addWidget(lPlayersReadyH,4, 1);
    gridLayout->addWidget(lPlayersReady.at(0),4, 2);
    gridLayout->addWidget(lPlayersReady.at(1),4, 3);
    gridLayout->addWidget(lPlayersReady.at(2),4, 4);
    gridLayout->addWidget(lPlayersReady.at(3),4, 5);
    gridLayout->addWidget(runButton,5, 2);
    gridLayout->addWidget(quitButton,5, 3);

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
    if(checkAvailableSocket())
    {
        msg = "serverConnectionOk#";
        msg.append(QString::number(playerNumber));
        lPlayersConnected.at(playerNumber-1)->setText("Connected");
        lPlayersReady.at(playerNumber-1)->setText("n/a");
        qDebug()<<"SERVER: onNewClientRequest / msg =" << msg;
    }
    else
    {
        msg = "noMoreSocketAvailable";
        qDebug()<<"SERVER: onNewClientRequest / header = noMoreSocketAvailable";
    }
    //msg += "#" + playerNumber;

    buildClientResponse(msg);
    //sendClientResponse();

    if(activeSocket == NULL)
        qDebug()<<"SERVER: onNewClientRequest END / activeSocket == NULL";
    else
    {
        qDebug()<<"SERVER: onNewClientRequest END / activeSocket: "<<activeSocket->state();
    }
    endConversation();
}

void Server::endConversation()
{
    activeSocket = NULL;
    playerNumber = 0;
    blockSize =0;
    qDebug()<<"SERVER: endConversation / END";
}

void Server::readRequest()
{
    qDebug()<<"SERVER: readRequest / header before = " << clientMessage;
    qDebug()<<"SERVER: readRequest / Hash.size() = " << clientConnections.size();

    //QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    activeSocket = qobject_cast<QTcpSocket*>(sender());

    playerNumber = clientConnections.indexOf(activeSocket)+1;
    if(playerNumber == -1)
    {
        qDebug()<<"SERVER: readRequest / id in Hash not foud / ERROR ";
        return;
    }
    qDebug()<<"SERVER: readRequest / id in Hash = " << playerNumber;
    QDataStream in(activeSocket);
    in.setVersion(QDataStream::Qt_4_0);

    qDebug() << "SERVER: readRequest / activeSocket->bytesAvailable() " << activeSocket->bytesAvailable();

    if (blockSize == 0) {
        if (activeSocket->bytesAvailable() < (int)sizeof(quint16))
        {
            qDebug()<<"SERVER: readRequest / activeSocket->bytesAvailable() < (int)sizeof(quint16)";
            return;
        }

        in >> blockSize;
    }

    if (activeSocket->bytesAvailable() < blockSize)
    {
        qDebug()<<"SERVER: readRequest / activeSocket->bytesAvailable() < blockSize";
        return;
    }

    qDebug() << "SERVER: readRequest / activeSocket->bytesAvailable() " << activeSocket->bytesAvailable();

    in >> clientMessage;

    qDebug() << "blockSize" <<blockSize;
    qDebug() << "clientMessage" <<clientMessage;

    char *s = new char[activeSocket->bytesAvailable()];
    int n = in.readRawData(s,activeSocket->bytesAvailable());
    //qDebug() << "----------------------------------";
    /*for (int i=0; i <n; i++)
        qDebug() << (int)s[i];*/
    //qDebug() << n;
    //qDebug() << "status :" << in.status();
    //return;

    QList<QString> listMsg = parse(clientMessage);

    qDebug() << "SERVER: readRequest / before headerRead playerNumber = " << playerNumber;

    QString rep;
    if(listMsg.at(0) == "ReadyRun")
    {
        if(!gameRunning)
        {
            rep = playerReady();
        }
        // else throw exception XXX_GAME_IS_RUNNING;
    }
    else if (listMsg.at(0) == "checkUserName"){
        if(!gameRunning)
            rep = checkPlayerName(listMsg.at(1));
        else
            rep = "gameIsRunning!";
        // else throw exception XXX_GAME_NOT_RUNNING;
    }
    else if (listMsg.at(0) == "playerStatusRequest"){
        if(gameRunning)
            sendPlayerStatus();
        // else throw exception XXX_GAME_NOT_RUNNING;
    }/*
    else if(header == "playerAction"){
        if(gameRunning)
            requestServerConnection();
            //playerAction();
        // else throw exception XXX_GAME_NOT_RUNNING;
    }*/
    else
    {
        qDebug()<<"SERVER: readRequest / no planned action";
        rep = "NODATA";
        // throw exception XXX_BAD_CLIENT_REQUEST;
    }

    buildClientResponse(rep);
    //sendClientResponse();
    endConversation();
}

QList<QString> Server::parse(QString clientMessage)
{
    QList<QString> listMsg = clientMessage.split("#");
    return listMsg;
}

bool Server::checkAvailableSocket()
{
    activeSocket = tcpServer->nextPendingConnection();
    //QTcpSocket clientConnection = tcpServer->nextPendingConnection();

    if(clientsConnectedNb < maxPlayers){

        clientsConnectedNb++;

        playerNumber = clientsConnectedNb;

        //clientConnections->append(clientConnection);
        clientConnections.append(activeSocket);

        connect(activeSocket, SIGNAL(readyRead()), this, SLOT(readRequest()));

        //clientConnection[playerId.toInt()] = tcpServer->nextPendingConnection();
        //connect(clientConnection[playerId.toInt()], SIGNAL(readyRead()), this, SLOT(readRequest()));

        qDebug()<<"SERVER: checkAvailableSocket / playerNumber: "<<playerNumber;

        return true;
    }
    else
    {
        clientWaitingList.append(activeSocket);
        return false;
    }
}

QString Server::checkPlayerName(QString playerName)
{
    qDebug()<<"SERVER: checkPlayerName / playerName" << playerName;
    foreach(Player *player, listPlayers)
    {
        qDebug()<<"SERVER: checkPlayerName / playerName[i]" << player->getPlayerName();
        if(QString::compare(player->getPlayerName(), playerName) ==0)
            return "userNameTaken";
    }

    listPlayers.at(playerNumber-1)->setPlayerName(playerName);

    return "userNameOK";
}

QString Server::playerReady()
{
    qDebug()<<"SERVER: playerReady";

    //lPlayersReady.at(playerNumber-1)->setText("Ready");
    lPlayersReady.at(playerNumber-1)->setText(listPlayers.at(playerNumber-1)->addCount());
    clientMessage = "clientReady";

    blockSize = 0;
    return "OK";
}

void Server::buildClientResponse(QString msg)
{
    //block.clear();
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    qDebug()<<"SERVER: buildClientResponse / block.size() before: "<<block.size();

    qDebug()<<"SERVER: buildClientResponse / msg: "<<msg;

    out << (quint16)0;
    out << msg;
    out.device()->seek(0);
    qDebug()<<"SERVER: buildClientResponse / block.size() after: "<<block.size();
    qDebug()<<"SERVER: buildClientResponse / block.size()- sizeof(quint16) after: "<<block.size()- sizeof(quint16);
    out << (quint16)(block.size() - sizeof(quint16));

    QString w = QString::number(activeSocket->write(block));
    qDebug() << "w: " << w;
    activeSocket->flush();
}

void Server::sendClientResponse()
{

    if(activeSocket == NULL)
        qDebug()<<"SERVER: sendClientResponse / activeSocket == NULL";
    else
    {
        qDebug()<<"SERVER: sendClientResponse / activeSocket: "<<activeSocket->state();
    }
    qDebug()<<"SERVER: sendClientResponse / playerNumber: "<<playerNumber;
    //activeSocket->write(block);
    qDebug()<<"SERVER: sendClientResponse / write done";
    //clientConnection[playerId]->disconnectFromHost();
    //qDebug()<<"SERVER: sendClientResponse/ disconnected";
}

void Server::sendPlayerStatus()
{
    qDebug()<<"SERVER: sendPlayerStatus";
    QByteArray block;

    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    clientMessage = "playerStatus";

    out << (quint16)0;
    out << clientMessage;
    for(int i=0;i<=maxPlayers;i++)
    {
        out << listPlayers.at(i)->getPoints();
    }
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
}
