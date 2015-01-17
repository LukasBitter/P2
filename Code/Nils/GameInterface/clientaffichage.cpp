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

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

ClientAffichage::ClientAffichage(int port, QWidget *parent, bool isHost) :
    QWidget(parent)
{
    setWindowTitle(tr("Basic RTS Game"));
    setUI();

//    if(isHost)
//        server = new Server();
//    else
//        server = 0;

//    client = new Client(this, isHost, port);

    connect(hostCombo, SIGNAL(editTextChanged(QString)),
            this, SLOT(enableGetConnectionButton()));
    connect(portLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(enableGetConnectionButton()));
    connect(getConnectionButton, SIGNAL(clicked()),
            client, SLOT(requestNewConnection()));
    connect(readyButton, SIGNAL(clicked()), this, SLOT(ReadyRun()));
    connect(runButton, SIGNAL(clicked()), this, SLOT(runGame()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
}

ClientAffichage::~ClientAffichage()
{
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

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

void ClientAffichage::userNameOk()
{
    this->statusLabel->setText(tr("Connection established. Press \"Ready\" when readyto start"));
    readyButton->setEnabled(true);
    userNameLineEdit->setDisabled(true);
    updateScreen();
}

void ClientAffichage::userNameTaken()
{
    this->statusLabel->setText(tr("userName already taken. Choose another one"));
    getConnectionButton->setText(tr("Validate Name"));
    getConnectionButton->setEnabled(true);
    updateScreen();
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void ClientAffichage::setUI()
{
    //Creation de l'interface
    buttonBox = new QDialogButtonBox(this);
    readyButton = new QPushButton(tr("Ready"), this);
    runButton = new QPushButton(tr("Run"), this);
    quitButton = new QPushButton(tr("Quit"), this);
    getConnectionButton = new QPushButton(tr("Connection"), this);
    hostCombo = new QComboBox(this);
    portLineEdit = new QLineEdit(this);
    userNameLineEdit = new QLineEdit(this);
    portLineEdit->setValidator(new QIntValidator(1, 65535, this));
    statusLabel = new QLabel(tr("To play a Basic RTS, you must run"
                                "Delete Game Server as well."), this);



    runButton->setEnabled(false);
    hostCombo->setEditable(true);
    readyButton->setEnabled(false);
    getConnectionButton->setDefault(true);
    getConnectionButton->setEnabled(false);

    buttonBox->addButton(getConnectionButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(readyButton, QDialogButtonBox::RejectRole);
    buttonBox->addButton(runButton, QDialogButtonBox::RejectRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    portLineEdit->setFocus();

    QLabel *lPlayerNumberH = new QLabel(tr("Player: "),this);
    QLabel *lPlayerNameH = new QLabel(tr("Name: "),this);
    QLabel *lPlayersConnectedH = new QLabel(tr("Connection: "),this);
    QLabel *lPlayersReadyH = new QLabel(tr("Ready: "),this);
    QLabel *hostLabel = new QLabel(tr("&Server name:"),this);
    QLabel *portLabel = new QLabel(tr("S&erver port:"),this);
    QLabel *userNameLabel = new QLabel(tr("&User name:"),this);

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

