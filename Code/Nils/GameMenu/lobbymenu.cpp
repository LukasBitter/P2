#include "lobbymenu.h"
#include "GameConnexion/gameclient.h"
#include "GameConnexion/gameserver.h"
#include "gamecontext.h"
#include "gamerlist.h"
#include "GameComponent/gamer.h"

#include <QPushButton>
#include <QTableWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QStringList>
#include <QStandardItem>


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

LobbyMenu::LobbyMenu(QWidget *parent) :  QWidget(parent),
    server(0), client(0), maxGamer(4), host(false)
{
    setUpUI();
    disableUI();

    connect(btReturn,SIGNAL(clicked()),this,SLOT(onBtReturnPressed()));
    connect(btConnect,SIGNAL(clicked()),this,SLOT(onBtConnectPressed()));
    connect(btStart,SIGNAL(clicked()),this,SLOT(onBtStartPressed()));
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void LobbyMenu::enableClientUI()
{
    disableUI();
    cbbReady->setEnabled(true);
    btConnect->setEnabled(true);
    txtAdressIP->setEnabled(true);

    host = false;
}

void LobbyMenu::enableServerUI()
{
    disableUI();
    cbxMap->setEnabled(true);
    btStart->setEnabled(true);
    cbbReady->setEnabled(true);
    btConnect->setEnabled(true);

    setServer(new GameServer(maxGamer, this));
    host = true;
}

void LobbyMenu::updateUI()
{
    qDebug()<<"LobbyMenu : enter 'updateUI'";

    tblStatus->clearContents(); //Detruit également les pointeurs
    int cpt = 0;
    foreach (Gamer *g, GamerList::getLstGamer())
    {
        QString &s1 = *new QString("%1");
        s1.arg(cpt);
        QString &s2 = *new QString("%1");
        s2.arg(*g->getName());
        tblStatus->setItem(cpt, 0, new QTableWidgetItem(s1));
        tblStatus->setItem(cpt, 1, new QTableWidgetItem(s2));
        ++cpt;
    }
}

void LobbyMenu::launchGame()
{
    qDebug()<<"LobbyMenu : enter 'launchGame'";
    GameContext *gc = 0;
    if( host && client != 0 && server != 0)
    {
        qDebug()<<"LobbyMenu : launch game as host";
        gc = new GameContext(client, server);
    }
    else if(!host && client != 0)
    {
        qDebug()<<"LobbyMenu : launch game as client";
        gc = new GameContext(client);
    }
    else
    {
        qCritical()<<"LobbyMenu : unexpected case in 'launchGame'";
    }

    if(gc != 0)
    {
        emit play(gc);
    }
}

void LobbyMenu::showError(QAbstractSocket::SocketError err)
{
    qWarning()<<"LobbyMenu : enter 'showError'"<<err;
    if(host)
    {
        btConnect->setEnabled(true);
        txtAdressIP->setEnabled(true);
    }

    QMessageBox msgBox;
    msgBox.setText("ERREUR");
    msgBox.exec();
}

void LobbyMenu::onBtReturnPressed()
{
    qDebug()<<"LobbyMenu : want switch to menu";
    emit returnToMenu();
}

void LobbyMenu::onBtConnectPressed()
{
    qDebug()<<"LobbyMenu : enter 'onBtConnectPressed'";
    btConnect->setEnabled(false);
    txtAdressIP->setEnabled(false);

    if(host)
    {
        qDebug()<<"LobbyMenu : create client as host";
        setClient(new GameClient("127.0.0.1", this));
    }
    else
    {
        qDebug()<<"LobbyMenu : create client as client";
        setClient(new GameClient(txtAdressIP->text(), this));
    }
    connect(client,SIGNAL(switchToGame()),this,SLOT(launchGame()));
    connect(client,SIGNAL(errorOccured(QAbstractSocket::SocketError)),
            this,SLOT(showError(QAbstractSocket::SocketError)));
    connect(client,SIGNAL(connexionOk()),this,SLOT(onSuccessfulConnexion()));
    connect(client,SIGNAL(updateLobby()),this,SLOT(updateUI()));
}

void LobbyMenu::onBtStartPressed()
{
    qDebug()<<"LobbyMenu : enter 'onBtStartPressed'";
    if(client != 0)
    {
        client->launchGame(
                "10.3.4/8.6.4/9.5.3/7.6.3/@6.90.-90.50.110.-1/4.0.0.30.100.2/5.180.100.10.10.-1/3.180.0.50.100.1/",
                "10.150_30_2_1,/8./9./7./@6.50,1,-1,0/4.20,1,2,0/5.0,1,-1,0/3.50,1,1,0/");
    }
    else
    {
        qCritical()<<"LobbyMenu : unexpected case in 'onBtStartPressed'";
    }
}

void LobbyMenu::onSuccessfulConnexion()
{
    qDebug()<<"LobbyMenu : successfull connexion to server";
    QMessageBox msgBox;
    msgBox.setText("Connextion au serveur avec succes");
    msgBox.exec();
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void LobbyMenu::setUpUI()
{
    this->btStart = new QPushButton("Start game", this);
    this->cbbReady = new QCheckBox("Ready", this);
    this->cbxMap = new QComboBox(this);
    this->tblStatus = new QTableWidget(this);
    this->txtAdressIP = new QLineEdit("Enter host IP",this);
    this->btConnect = new QPushButton("Connection",this);
    this->btReturn = new QPushButton("Return",this);

    tblStatus->setRowCount(maxGamer);
    tblStatus->setColumnCount(4);
    QStringList &s = *new QStringList();
    s<<"Num joueur"<<"Nom joueur"<<"Couleur"<<"Pret";
    tblStatus->setHorizontalHeaderLabels(s);

    QGridLayout *l = new QGridLayout(this);
    l->addWidget(txtAdressIP, 0,0,1,2);
    l->addWidget(btConnect, 0,2);
    l->addWidget(tblStatus, 1,0,1,3);
    l->addWidget(cbxMap, 2,0,1,3);
    l->addWidget(btReturn, 3,0);
    l->addWidget(cbbReady, 3,1);
    l->addWidget(btStart, 3,2);

    this->setLayout(l);
}

void LobbyMenu::disableUI()
{
    cbxMap->setEnabled(false);
    btStart->setEnabled(false);
    cbbReady->setEnabled(false);
    btConnect->setEnabled(false);
    txtAdressIP->setEnabled(false);

    setClient(0);
    setServer(0);
}

void LobbyMenu::setClient(GameClient *c)
{
    qDebug()<<"LobbyMenu : enter 'setClient'";
    if(client != 0)
    {
        qDebug()<<"LobbyMenu : delete client";
        delete client;
    }
    client = c;
}

void LobbyMenu::setServer(GameServer *s)
{
    qDebug()<<"LobbyMenu : enter 'setServer'";
    if(server != 0)
    {
        qDebug()<<"LobbyMenu : delete server";
        delete server;
    }
    server = s;
}
