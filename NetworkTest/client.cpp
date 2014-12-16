#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>

#include "client.h"
#include "deletegame.h"

Client::Client(QWidget *parent) :
    QDialog(parent), networkSession(0)
{
    hostLabel = new QLabel(tr("&Server name:"));
    portLabel = new QLabel(tr("S&erver port:"));

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
    portLineEdit->setValidator(new QIntValidator(1, 65535, this));

    hostLabel->setBuddy(hostCombo);
    portLabel->setBuddy(portLineEdit);

    statusLabel = new QLabel(tr("To play a Delete game, you must run"
                                "Delete Game Server as well."));

    getConnectionButton = new QPushButton(tr("Connection"));
    getConnectionButton->setDefault(true);
    getConnectionButton->setEnabled(false);

    playerId = "NULL";

    runButton = new QPushButton(tr("Run"));
    runButton->setEnabled(false);
    quitButton = new QPushButton(tr("Quit"));

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(getConnectionButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(runButton, QDialogButtonBox::RejectRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

//! [1]
    tcpSocket = new QTcpSocket(this);
//! [1]

    connect(hostCombo, SIGNAL(editTextChanged(QString)),
            this, SLOT(enableGetConnectionButton()));
    connect(portLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(enableGetConnectionButton()));
    connect(getConnectionButton, SIGNAL(clicked()),
            this, SLOT(requestNewConnection()));
    connect(runButton, SIGNAL(clicked()), this, SLOT(ReadyRun()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
//! [2] //! [3]
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readServerResponse()));
    //connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readFortune()));
//! [2] //! [4]
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
//! [3]
            this, SLOT(displayError(QAbstractSocket::SocketError)));
//! [4]

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(hostLabel, 0, 0);
    mainLayout->addWidget(hostCombo, 0, 1);
    mainLayout->addWidget(portLabel, 1, 0);
    mainLayout->addWidget(portLineEdit, 1, 1);
    mainLayout->addWidget(statusLabel, 2, 0, 1, 2);
    mainLayout->addWidget(buttonBox, 3, 0, 1, 2);
    setLayout(mainLayout);

    setWindowTitle(tr("Delete Game Client"));
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

void Client::requestNewConnection()
{

    qDebug()<<"CLIENT: requestNewConnection";
    getConnectionButton->setEnabled(false);
    blockSize = 0;

    /*
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)0;
    out << "connectionRequest";
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    */

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
    runButton->setEnabled(false);
    blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    QString sReadyRun;
    sReadyRun = "ReadyRun";

    out << (quint16)0;
    out << sReadyRun;
    out << playerId;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    qDebug()<<"CLIENT: ReadyRun / String: "<<sReadyRun;
    qDebug()<<"CLIENT: ReadyRun / playerId: "<<playerId;


    tcpSocket->write(block);
    //tcpSocket->abort();
    //tcpSocket->connectToHost(hostCombo->currentText(),
    //                         portLineEdit->text().toInt());
}


void Client::readServerResponse()
{
    //QDataStream in(tcpSocket);
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    qDebug()<<"CLIENT: readServerResponse / blockSize: " << blockSize;

    if (blockSize == 0) {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16)){
            qDebug()<<"CLIENT: readServerResponse / bytesAvailable() < (int)sizeof(quint16)";
            return;
        }

        in >> blockSize;
    }

    if (tcpSocket->bytesAvailable() < blockSize)
    {
        qDebug()<<"CLIENT: readServerResponse / bytesAvailable() < blockSize";
        return;
    }

    QString serverHeader;
    in >> serverHeader;

    qDebug()<<"CLIENT: serverHeader: "<<serverHeader;

/*
    QString id;
    in >> id;

    playerId = id;


    qDebug()<<"CLIENT: setPlayerId / playerId: "<<id;
*/
    if (serverHeader == "serverConnectionOk") {
        setPlayerId();
    }
}

void Client::setPlayerId()
{
    QString id;
    in >> id;

    playerId = id;

    qDebug()<<"CLIENT: setPlayerId / id: "<<id;
    qDebug()<<"CLIENT: setPlayerId / playerId: "<<playerId;

    runButton->setEnabled(true);
}

