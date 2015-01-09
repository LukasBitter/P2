#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>
#include <QStringBuilder>

#include "client.h"
#include "deletegame.h"

Client::Client(QWidget *parent) :
    QDialog(parent), networkSession(0)
{
    maxPlayers = 4;
    hostCombo = new QComboBox;
    hostCombo->setEditable(true);

    // find out name of this machine
    QString name = QHostInfo::localHostName();
    if (!name.isEmpty()) {
        hostCombo->addItem(name);
        QString domain = QHostInfo::localDomainName();
        if (!domain.isEmpty())
            hostCombo->addItem(name + QChar('.') + domain);
    }
    if (name != QString("localhost"))
        hostCombo->addItem(QString("localhost"));
    // find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (!ipAddressesList.at(i).isLoopback())
            hostCombo->addItem(ipAddressesList.at(i).toString());
    }
    // add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback())
            hostCombo->addItem(ipAddressesList.at(i).toString());
    }

    portLineEdit = new QLineEdit;
    userNameLineEdit = new QLineEdit;
    portLineEdit->setValidator(new QIntValidator(1, 65535, this));


    statusLabel = new QLabel(tr("To play a Delete game, you must run"
                                "Delete Game Server as well."));

    getConnectionButton = new QPushButton(tr("Connection"));
    getConnectionButton->setDefault(true);
    getConnectionButton->setEnabled(false);

    playerNumber = "NULL";

    readyButton = new QPushButton(tr("Run"));
    readyButton->setEnabled(false);
    quitButton = new QPushButton(tr("Quit"));

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(getConnectionButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(readyButton, QDialogButtonBox::RejectRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    tcpSocket = new QTcpSocket(this);

    connect(hostCombo, SIGNAL(editTextChanged(QString)),
            this, SLOT(enableGetConnectionButton()));
    connect(portLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(enableGetConnectionButton()));
    connect(getConnectionButton, SIGNAL(clicked()),
            this, SLOT(requestNewConnection()));
    connect(readyButton, SIGNAL(clicked()), this, SLOT(ReadyRun()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readServerResponse()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    init();
    setUI();

    setWindowTitle(tr("Basic RTS Game"));
    portLineEdit->setFocus();

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

        //getFortuneButton->setEnabled(false);
        statusLabel->setText(tr("Opening network session."));
        networkSession->open();
    }
}

void Client::setUI()
{
    QLabel *lPlayerH = new QLabel(tr("Player: "));
    QLabel *lPlayersConnectedH = new QLabel(tr("Connexion: "));
    QLabel *lPlayersReadyH = new QLabel(tr("Ready: "));
    QLabel *hostLabel = new QLabel(tr("&Server name:"));
    QLabel *portLabel = new QLabel(tr("S&erver port:"));
    QLabel *userNameLabel = new QLabel(tr("&User name:"));

    QGridLayout *gridLayout= new QGridLayout(this);
    gridLayout->setColumnStretch(1, 15);
    gridLayout->setColumnStretch(2, 30);
    gridLayout->setColumnStretch(3, 30);
    gridLayout->setColumnStretch(4, 30);
    gridLayout->setColumnStretch(5, 30);

    gridLayout->setRowStretch(1,10);
    gridLayout->setRowStretch(2,10);
    gridLayout->setRowStretch(3,10);
    gridLayout->setRowStretch(4,10);
    gridLayout->setRowStretch(5,10);
    gridLayout->setRowStretch(6,10);
    gridLayout->setRowStretch(7,10);

    gridLayout->addWidget(hostLabel, 0, 1);
    gridLayout->addWidget(hostCombo, 0, 2, 1, 3);
    gridLayout->addWidget(portLabel, 1, 1);
    gridLayout->addWidget(portLineEdit, 1, 2, 1, 3);
    gridLayout->addWidget(userNameLabel, 2, 1);
    gridLayout->addWidget(userNameLineEdit, 2, 2, 1, 3);
    gridLayout->addWidget(lPlayerH,3, 1);
    gridLayout->addWidget(lPlayersNumbers.at(0),3, 2);
    gridLayout->addWidget(lPlayersNumbers.at(1),3, 3);
    gridLayout->addWidget(lPlayersNumbers.at(2),3, 4);
    gridLayout->addWidget(lPlayersNumbers.at(3),3, 5);
    gridLayout->addWidget(lPlayersConnectedH,4, 1);
    gridLayout->addWidget(lPlayersConnected.at(0),4, 2);
    gridLayout->addWidget(lPlayersConnected.at(1),4, 3);
    gridLayout->addWidget(lPlayersConnected.at(2),4, 4);
    gridLayout->addWidget(lPlayersConnected.at(3),4, 5);
    gridLayout->addWidget(lPlayersReadyH,5, 1);
    gridLayout->addWidget(lPlayersReady.at(0),5, 2);
    gridLayout->addWidget(lPlayersReady.at(1),5, 3);
    gridLayout->addWidget(lPlayersReady.at(2),5, 4);
    gridLayout->addWidget(lPlayersReady.at(3),5, 5);
    gridLayout->addWidget(statusLabel, 6, 1, 1, 2);
    gridLayout->addWidget(buttonBox, 7, 0, 1, 2);
    gridLayout->addWidget(readyButton,7, 2, 1, 2);
    gridLayout->addWidget(quitButton,7, 4, 1, 2);

    hostLabel->setBuddy(hostCombo);
    portLabel->setBuddy(portLineEdit);
}

void Client::init(){
    for(int i= 0; i<maxPlayers;i++)
    {
        lPlayersNumbers.append(new QLabel(QString("#").append(QString::number(i+1))));
        lPlayersNames.append(new QLabel("n/a"));
        lPlayersConnected.append(new QLabel("n/a"));
        lPlayersReady.append(new QLabel(""));
    }
    playersInGame = 0;
    blockSize = 0;

//    lPlayerH = new QLabel(tr("Player: "));
//    lPlayersConnectedH = new QLabel(tr("Connexion: "));
//    lPlayersReadyH = new QLabel(tr("Ready: "));
    gameRunning= 0;
}

void Client::requestNewConnection()
{
    if(userNameLineEdit->text().isEmpty())
    {
        setStatus("Insert your name");
        return;
    }

    qDebug()<<"CLIENT: requestNewConnection";
    getConnectionButton->setEnabled(false);
    blockSize = 0;

    tcpSocket->abort();
    tcpSocket->connectToHost(hostCombo->currentText(),
                             portLineEdit->text().toInt());
}

void Client::displayError(QAbstractSocket::SocketError socketError)
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
                                 tr("The connection was refused by the peer. "
                                    "Make sure the Delete Game server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Delete Game Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
    }

    //getFortuneButton->setEnabled(true);
}

void Client::enableGetConnectionButton()
{
    getConnectionButton->setEnabled((!networkSession || networkSession->isOpen()) &&
                                 !hostCombo->currentText().isEmpty() &&
                                 !portLineEdit->text().isEmpty());

}

void Client::sessionOpened()
{
    // Save the used configuration
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

    statusLabel->setText(tr("This client requires that you run the "
                            " Delete Game Server example as well."));

    enableGetConnectionButton();
}

void Client::runGame()
{
    game = new deleteGame();
    //this->hide();
    game->show();
}

void Client::ReadyRun()
{
    qDebug()<<"CLIENT: ReadyRun / tcpSocket->state() / 1: "<<tcpSocket->state();
//    runButton->setEnabled(false);
    blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    qDebug()<<"CLIENT: ReadyRun / block.size() before: "<<block.size();

    QString sReadyRun("ReadyRun#");
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
    qDebug()<<"CLIENT: sendServerMessage";
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)0;
    //out << headerOut;
    out << msg;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    //qDebug()<<"CLIENT: sendServerMessage / headerOut: "<<headerOut;
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
                in >> blockSize;
                qDebug()<<"CLIENT: readServerResponse / blockSize after: " << blockSize;
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

        QList<QString> listMsg = parse(serverMessage);
        QString msgOut;

        qDebug()<<"CLIENT: readServerResponse / serverHeader: "<<serverMessage;
        bool sendMessage = false;

        //test
        /*if(serverMessage == "")
        {
            for (int i= 0;i<4;i++)
            {
                in>>serverMessage;
                qDebug() << "Header" << i << ": " << serverMessage;
            }
        }*/


        if (listMsg.at(0) == "serverConnectionOk")
        {
            qDebug()<<"CLIENT: readServerResponse / setPlayerId";
            setPlayerNumber(listMsg.at(1));
            setStatus("Connected to server. Checking user name");
            msgOut = "checkUserName";
            msgOut += "#" + userNameLineEdit->text();
            //sendServerMessage(userNameLineEdit->text());
            sendMessage = true;
        }
        else if (listMsg.at(0) == "userNameOK")
        {
            setStatus("Connection established. Press RUN when ready");
            readyButton->setEnabled(true);
        }
        else if (listMsg.at(0) == "userNameTaken")
        {
            setStatus("userName already taken. Choose another one");
            getConnectionButton->setEnabled(true);
        }
        else if (listMsg.at(0) == "noMoreSocketAvailable" )
            setStatus("game full!");
        else if (listMsg.at(0) == "clientReady" )
            setStatus("Ready for game to begin. Wait for server to start game");
        else if (listMsg.at(0) == "OK" )
            // do nothing
            ;
        else
        {
            setStatus("could not read server header");
        }
        blockSize = 0;

        if(sendMessage)
        {
            qDebug()<<"CLIENT: sendServerMessage";
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_4_0);

            out << (quint16)0;
            //out << headerOut;
            out << msgOut;
            out.device()->seek(0);
            out << (quint16)(block.size() - sizeof(quint16));

            qDebug()<<"CLIENT: sendServerMessage / headerOut: "<<headerOut;
            qDebug()<<"CLIENT: sendServerMessage / msg: "<<msgOut;

            tcpSocket->write(block);
            tcpSocket->flush();
        }
     }
}

void Client::setStatus(QString msg)
{
    statusLabel->setText(msg);
}

void Client::setPlayerNumber(QString number)
{
    playerNumber = number;

    qDebug()<<"CLIENT: setPlayerId / playerId: "<<playerNumber;

}

QList<QString> Client::parse(QString clientMessage)
{
    QList<QString> listMsg = clientMessage.split("#");
    return listMsg;
}
