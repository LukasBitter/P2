#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>

#include <stdlib.h>
#include "server.h"

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
    header = "";
    playerId ="0";

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

        //clientConnection[4] = new QTcpSocket(this);
        //clientConnections = new QHash<int, QTcpSocket*>;
        //clientRequest = new QTcpSocket(this);

        connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
        connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewClientRequest()));
        //connect(clientConnection[0], SIGNAL(readyRead()), this, SLOT(readRequest()));
        //connect(clientConnection[2], SIGNAL(readyRead()), this, SLOT(readRequest()));
        //connect(clientConnection[3], SIGNAL(readyRead()), this, SLOT(readRequest()));
        //connect(clientConnection[4], SIGNAL(readyRead()), this, SLOT(readRequest()));
        //connect(clientConnection[0], SIGNAL(readyRead()), this, SLOT(readRequest()));
        //connect(clientConnection[0], SIGNAL(disconnected()), clientConnection[0], SLOT(deleteLater()));


        init();

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

        QLabel *lplayerH = new QLabel(tr("Player: "));
        QLabel *lplayersConnectedH = new QLabel(tr("Connexion: "));
        QLabel *lplayersReadyH = new QLabel(tr("Ready: "));

        QLabel *lplayer1 = new QLabel(tr("#1"));
        QLabel *lplayer2 = new QLabel(tr("#2"));
        QLabel *lplayer3 = new QLabel(tr("#3"));
        QLabel *lplayer4 = new QLabel(tr("#4"));

        gridLayout->addWidget(statusLabel,1, 1, 1, 4);
        gridLayout->addWidget(lplayerH,2, 1);
        gridLayout->addWidget(lplayer1,2, 2);
        gridLayout->addWidget(lplayer2,2, 3);
        gridLayout->addWidget(lplayer3,2, 4);
        gridLayout->addWidget(lplayer4,2, 5);
        gridLayout->addWidget(lplayersConnectedH,3, 1);
        gridLayout->addWidget(lPlayersConnected.at(0),3, 2);
        gridLayout->addWidget(lPlayersConnected.at(1),3, 3);
        gridLayout->addWidget(lPlayersConnected.at(2),3, 4);
        gridLayout->addWidget(lPlayersConnected.at(3),3, 5);
        gridLayout->addWidget(lplayersReadyH,4, 1);
        gridLayout->addWidget(lPlayersReady.at(0),4, 2);
        gridLayout->addWidget(lPlayersReady.at(1),4, 3);
        gridLayout->addWidget(lPlayersReady.at(2),4, 4);
        gridLayout->addWidget(lPlayersReady.at(3),4, 5);
        gridLayout->addWidget(runButton,5, 2);
        gridLayout->addWidget(quitButton,5, 3);

        setWindowTitle(tr("Delete Game Server"));

}

void Server::init(){
    iPlayersPts[maxPlayers] = new int;
    for(int i= 0; i<maxPlayers;i++)
    {
        lPlayersConnected.insert("n/a");
        lPlayersReady.insert("");
        //lPlayersConnected[i] = QLabel("n/a");
        //lPlayersReady[i] = QLabel("");
        iPlayersPts[i] = maxPts;
    }
    playersInGame = 0;
    clientsConnectedNb = 0;
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
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    statusLabel->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                            "Wait until all players connect and run the Delete Game Client now:")
                         .arg(ipAddress).arg(tcpServer->serverPort()));
}

void Server::addPts()
{
    switch(playerId.toInt()){
    case 1: player1Pts++;
    case 2: player2Pts++;
    case 3: player3Pts++;
    }
}

void Server::delPts()
{
    switch(playerId.toInt()){
    case 1:
        player1Pts--;
        if (player1Pts == 0)
            playersInGame --;
        break;
    case 2:
        player2Pts--;
        if (player2Pts == 0)
            playersInGame --;
        break;
    case 3:
        player3Pts--;
        if (player3Pts == 0)
            playersInGame --;
        break;
    }

    checkEndGame();
}

void Server::checkEndGame()
{
    if (playersInGame > 0 && playersInGame < 2 ){
        gameRunning = false;
        /*if (player1Pts>0)
            emit playerWinsGame(1);
        else if (player2Pts>0)
            emit playerWinsGame(2);
        else if (player3Pts>0)
            emit playerWinsGame(3);
        else
            emit playerWinsGame(0);*/
    }
}

void Server::onNewClientRequest()
{

    //qDebug()<<"SERVER: onNewClientRequest / clientConnexion[2]: "<<clientConnection[2]->state();
    //qDebug()<<"SERVER: onNewClientRequest / clientConnexion[3]: "<<clientConnection[3]->state();
    QString msg;
    if(checkAvailableSocket())
    {
        msg = "serverConnectionOk";
    }
    else
        msg = "serverConnectionKo";

    buildClientResponse(msg);
    sendClientResponse();

    lPlayersConnected[playerId]->setText("Connected");
    lPlayersReady[playerId]->setText("n/a");


    if(activeSocket == NULL)
        qDebug()<<"SERVER: onNewClientRequest END / activeSocket == NULL";
    else
    {
        qDebug()<<"SERVER: onNewClientRequest END / activeSocket: "<<activeSocket->state();
    }
}

void Server::readRequest()
{
    qDebug()<<"SERVER: readRequest";

    qDebug()<<"SERVER: readRequest / header before = " << header;
    qDebug()<<"SERVER: readRequest / Hash.size() = " << clientConnections.size();

    //QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    activeSocket = qobject_cast<QTcpSocket*>(sender());

    for(int i=0;i<= clientConnections.size();i++)
    {
        if(activeSocket == clientConnections.find(i).value())
        {
            qDebug()<<"SERVER: readRequest / id in Hash = " << i;
            playerId = QString::number(i);
        }
    }

    QDataStream in(activeSocket);
    in.setVersion(QDataStream::Qt_4_0);

    qDebug() << "SERVER: readRequest / before headerRead playerId = " << playerId;


    qDebug()<<"SERVER: readRequest / before test blockSize = " << blockSize;

    if (blockSize == 0) {
        if (activeSocket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> blockSize;
    }

    if (activeSocket->bytesAvailable() < blockSize)
        return;

    qDebug()<<"SERVER: readRequest / after test blockSize = " << blockSize;

    QString header;
    in >> header;
    qDebug()<<"SERVER: readRequest / header = " << header;

    if(header == "ReadyRun")
    {
        if(!gameRunning)
        {
            //in >> playerId;
            playerReady();
        }
        // else throw exception XXX_GAME_IS_RUNNING;

    }
    else if (header == "playerStatusRequest"){
        if (gameRunning)
            sendPlayerStatus();
        // else throw exception XXX_GAME_NOT_RUNNING;
    }/*
    else if(header == "playerAction"){
        if (gameRunning)
            requestServerConnection();
            //playerAction();
        // else throw exception XXX_GAME_NOT_RUNNING;
    }*/
    else
        qDebug()<<"SERVER: readRequest / no planned action";
        // throw exception XXX_BAD_CLIENT_REQUEST;


    /*if (getDataStream())
    {
        getClientRequest();
        sendClientResponse(playerId);
    }*/
}

bool Server::checkAvailableSocket()
{
    if(playersInGame < maxPlayers){

        playersInGame++;
        //playerId = QString::number(playersInGame);

        activeSocket = tcpServer->nextPendingConnection();
        //QTcpSocket clientConnection = tcpServer->nextPendingConnection();

        playerId = QString::number(playersInGame);

        //clientConnections->append(clientConnection);
        clientConnections.insert(playersInGame, activeSocket);

        connect(activeSocket, SIGNAL(readyRead()), this, SLOT(readRequest()));

        //clientConnection[playerId.toInt()] = tcpServer->nextPendingConnection();
        //connect(clientConnection[playerId.toInt()], SIGNAL(readyRead()), this, SLOT(readRequest()));

        qDebug()<<"SERVER: checkAvailableSocket / playerId: "<<playerId;

        return true;
    }
    else
        return false;
}

void Server::setClientConnected()
{

}

void Server::playerReady()
{
    qDebug()<<"SERVER: playerReady";

    lPlayersReady[playerId]->setText("Ready");

    blockSize = 0;
}

void Server::sendClientResponse()
{

    if(activeSocket == NULL)
        qDebug()<<"SERVER: sendClientResponse / activeSocket == NULL";
    else
    {
        qDebug()<<"SERVER: sendClientResponse / activeSocket: "<<activeSocket->state();
    }
    qDebug()<<"SERVER: sendClientResponse / id: "<<playerId;
    activeSocket->write(block);
    qDebug()<<"SERVER: sendClientResponse / write done";
    //clientConnection[playerId]->disconnectFromHost();
    //qDebug()<<"SERVER: sendClientResponse/ disconnected";
}

void Server::sendPlayerStatus()
{
    qDebug()<<"SERVER: sendPlayerStatus";

    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    header = "playerStatus";

    out << (quint16)0;
    out << header;
    out << player1Pts;
    out << player2Pts;
    out << player3Pts;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
}

void Server::buildClientResponse(QString connexionMsg)
{

    if(activeSocket == NULL)
        qDebug()<<"SERVER: buildClientResponse / activeSocket == NULL";
    else
    {
        qDebug()<<"SERVER: buildClientResponse / activeSocket: "<<activeSocket->state();
    }
    block.clear();
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    //header = "serverConnectionOk";
    //QString id = QString::number(playerId); // a passer en paramèters depuis l'attribution de l'id
    qDebug()<<"SERVER: buildClientResponse / playerId: "<<playerId;

    out << (quint16)0;
    out << connexionMsg;
    out << playerId;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    blockSize = 0;
}

