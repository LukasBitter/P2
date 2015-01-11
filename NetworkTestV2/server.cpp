#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>

#include <stdlib.h>
#include "server.h"
#include <process.h>

#define SEP_CONX "#"
#define SEP_STATUS ";"

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
        lPlayersNames.append(new QLabel(""));
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
    if(checkAvailableSocket())
    {
        msg = "serverConnectionOk";
        msg.append(SEP_CONX);
        msg.append(QString::number(playerNumber));
        msg.append(SEP_CONX);
        msg.append(getPlayersStatus());
        lPlayersConnected.at(playerNumber-1)->setText("Connected");
        lPlayersReady.at(playerNumber-1)->setText("n/a");
    }
    else
        msg = "noMoreSocketAvailable";
    qDebug()<<"SERVER: onNewClientRequest / msg =" << msg;

    sendClientResponse(msg);
    endConversation();
}

QString Server::getPlayersStatus()
{
    QString rep;
    //rep= labelBuildString(lPlayersNumbers);
    QLabel *ele;
    foreach(ele, lPlayersNumbers)
        rep += ele->text().remove(0, 1) + SEP_STATUS;
    foreach(ele, lPlayersNames)
        rep += ele->text() + SEP_STATUS;
    foreach(ele, lPlayersConnected)
        rep += ele->text() + SEP_STATUS;
    foreach(ele, lPlayersReady)
        rep += ele->text() + SEP_STATUS;

    rep.remove(rep.length()-1, 1);
    qDebug() << "rep" << rep;
    return rep;
}

QString Server::labelBuildString(QList<QLabel> &list)
{
    QString str;
    QLabel ele;
    /*
    foreach(ele , list)
    {
        str += ele.text() + STATUS_SEP;
    }*/
    qDebug() <<"str: " << str;

    return str;
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
    //QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    activeSocket = qobject_cast<QTcpSocket*>(sender());

    playerNumber = clientConnections.indexOf(activeSocket)+1;
    if(playerNumber == -1)
    {
        qDebug()<<"SERVER: readRequest / id not foud in Hash / ERROR ";
        return;
    }
    qDebug()<<"SERVER: readRequest / id in Hash = " << playerNumber;
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

    QString rep = parse(clientMessage);
    sendClientResponse(rep);
    endConversation();
    if(rep.compare("userNameOK") == 0)
    {
        sendAllUsersStatus();
    }
}

void Server::sendAllUsersStatus()
{
    for (int i=0; i < maxPlayers; i++)
    {
        qDebug() << "SERVER: sendAllUsersStatus / lPlayersConnected: " << lPlayersConnected.at(i)->text()   ;
        qDebug() << "SERVER: sendAllUsersStatus / lPlayersConnected.at(i)->text().compare(\"Connected\"): " << lPlayersConnected.at(i)->text().compare("Connected");
        if(lPlayersConnected.at(i)->text().compare("Connected") == 0);
        {

            qDebug() << "SERVER: sendAllUsersStatus / lPlayersConnected: " << i;
            activeSocket = clientConnections.at(i);

            QString msg = "allUsersStatus";
            msg.append(SEP_CONX);
            msg.append(getPlayersStatus());

            sendClientResponse(msg);
        }
    }
}

QString Server::parse(QString clientMessage)
{
    QList<QString> listMsg = clientMessage.split(SEP_CONX);
    QString rep;

    if(listMsg.at(0) == "ReadyRun")
    {
        if(!gameRunning)
            rep = playerReady();
        else
            rep = "gameIsRunning!";
    }
    else if (listMsg.at(0) == "checkUserName")
    {
        if(!gameRunning)
            rep = checkPlayerName(listMsg.at(1));
        else
            rep = "gameIsRunning!";
    }
/*  else if(header == "playerAction"){
        if(gameRunning)
            requestServerConnection();
            //playerAction();
        // else throw exception XXX_GAME_NOT_RUNNING;
    }*/
    else
        rep = "NO PLANNED ACTION FOR";

    return rep;
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

    lPlayersNames.at(playerNumber-1)->setText(playerName);
    listPlayers.at(playerNumber-1)->setPlayerName(playerName);

    return "userNameOK";
}

QString Server::playerReady()
{
    qDebug()<<"SERVER: playerReady";

    lPlayersReady.at(playerNumber-1)->setText("Ready");
    return "clientReadyOK";
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
