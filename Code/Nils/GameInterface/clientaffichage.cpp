#include "clientaffichage.h"
#include "Connexion/client.h"
#include "Connexion/server.h"
#include "GameComponent/gamer.h"

#include <QComboBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include "Connexion/client.h"

ClientAffichage::ClientAffichage(int port, QWidget *parent, bool isHost) :
    QWidget(parent)
{
    readyButton = new QPushButton(tr("Ready"));
    readyButton->setEnabled(false);
    runButton = new QPushButton(tr("Run"));
    runButton->setEnabled(false);
    quitButton = new QPushButton(tr("Quit"));
    getConnectionButton = new QPushButton(tr("Connection"));
    getConnectionButton->setDefault(true);
    getConnectionButton->setEnabled(false);

    portLineEdit = new QLineEdit;

    userNameLineEdit = new QLineEdit;
    portLineEdit->setValidator(new QIntValidator(1, 65535, this));
    portLineEdit->setFocus();
    setWindowTitle(tr("Basic RTS Game"));

    statusLabel = new QLabel(tr("To play a Delete game, you must run"
                                "Delete Game Server as well."));

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(getConnectionButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(readyButton, QDialogButtonBox::RejectRole);
    buttonBox->addButton(runButton, QDialogButtonBox::RejectRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);


    connect(portLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(enableGetConnectionButton()));
    connect(getConnectionButton, SIGNAL(clicked()),
            this, SLOT(requestNewConnection()));
    connect(readyButton, SIGNAL(clicked()), this, SLOT(ReadyRun()));
    connect(runButton, SIGNAL(clicked()), this, SLOT(runGame()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    if(isHost)
    {
        client = new Client();
        server = new Server();
    }
    else
    {
        client = new Client();
        server = 0;
    }
    initLabels();
    setUI();
}


void ClientAffichage::setUI()
{
    QLabel *lPlayerNumberH = new QLabel(tr("Player: "));
    QLabel *lPlayerNameH = new QLabel(tr("Name: "));
    QLabel *lPlayersConnectedH = new QLabel(tr("Connection: "));
    QLabel *lPlayersReadyH = new QLabel(tr("Ready: "));
    QLabel *hostLabel = new QLabel(tr("&Server name:"));
    QLabel *portLabel = new QLabel(tr("S&erver port:"));
    QLabel *userNameLabel = new QLabel(tr("&User name:"));

    QGridLayout *gridLayout= new QGridLayout(this);

    gridLayout->addWidget(hostLabel, 0, 1);
    gridLayout->addWidget(hostCombo, 0, 2, 1, 3);
    gridLayout->addWidget(portLabel, 1, 1);
    gridLayout->addWidget(portLineEdit, 1, 2, 1, 3);
    gridLayout->addWidget(userNameLabel, 2, 1);
    gridLayout->addWidget(userNameLineEdit, 2, 2, 1, 3);
    gridLayout->addWidget(lPlayerNumberH,3, 1);
    gridLayout->addWidget(lPlayersNumbers.at(0),3, 2);
    gridLayout->addWidget(lPlayersNumbers.at(1),3, 3);
    gridLayout->addWidget(lPlayersNumbers.at(2),3, 4);
    gridLayout->addWidget(lPlayersNumbers.at(3),3, 5);
    gridLayout->addWidget(lPlayerNameH,4, 1);
    gridLayout->addWidget(lPlayersNames.at(0),4, 2);
    gridLayout->addWidget(lPlayersNames.at(1),4, 3);
    gridLayout->addWidget(lPlayersNames.at(2),4, 4);
    gridLayout->addWidget(lPlayersNames.at(3),4, 5);
    gridLayout->addWidget(lPlayersConnectedH,5, 1);
    gridLayout->addWidget(lPlayersConnected.at(0),5, 2);
    gridLayout->addWidget(lPlayersConnected.at(1),5, 3);
    gridLayout->addWidget(lPlayersConnected.at(2),5, 4);
    gridLayout->addWidget(lPlayersConnected.at(3),5, 5);
    gridLayout->addWidget(lPlayersReadyH,6, 1);
    gridLayout->addWidget(lPlayersReady.at(0),6, 2);
    gridLayout->addWidget(lPlayersReady.at(1),6, 3);
    gridLayout->addWidget(lPlayersReady.at(2),6, 4);
    gridLayout->addWidget(lPlayersReady.at(3),6, 5);
    gridLayout->addWidget(statusLabel, 7, 1, 1, 2);
    gridLayout->addWidget(buttonBox, 8, 0, 1, 4);

    hostLabel->setBuddy(hostCombo);
    portLabel->setBuddy(portLineEdit);
}

void ClientAffichage::initLabels(){
    for(int i= 0; i<client->getMaxPlayers() ;++i)
    {
        lPlayersNumbers.append(new QLabel(QString("#").append(QString::number(i+1))));
        lPlayersNames.append(new QLabel("n/a"));
        lPlayersConnected.append(new QLabel("n/a"));
        lPlayersReady.append(new QLabel(""));
    }
}

void ClientAffichage::updateScreen()
{
    int i;
    foreach(Gamer *ele, Gamer::getLstGamer())
    {
        i = ele->getId();
        lPlayersNames.at(i)->setText(*ele->getName());
        lPlayersConnected.at(i)->setText(QString::number(ele->isConnected()));
        lPlayersReady.at(i)->setText(QString::number(ele->isReady()));
    }
}
