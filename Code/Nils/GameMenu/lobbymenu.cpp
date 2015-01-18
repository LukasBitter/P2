#include "lobbymenu.h"
#include "GameConnexion/gameclient.h"
#include "GameConnexion/gameserver.h"
#include "gamecontext.h"

#include <QPushButton>
#include <QTableView>
#include <QCheckBox>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QLineEdit>
#include <QMessageBox>

LobbyMenu::LobbyMenu(QWidget *parent) :  QWidget(parent),
    server(0), client(0), maxGamer(4), host(false)
{
    setUpUI();
    disableUI();

    connect(btReturn,SIGNAL(clicked()),this,SLOT(onBtReturnPressed()));
    connect(btConnect,SIGNAL(clicked()),this,SLOT(onBtConnectPressed()));
    connect(btStart,SIGNAL(clicked()),this,SLOT(onBtStartPressed()));
}

void LobbyMenu::updateUI()
{

}

void LobbyMenu::launchGame()
{
    qDebug()<<"launchGame";
    GameContext *gc = 0;
    if( host && client != 0 && server != 0)
    {
        gc = new GameContext(client, server);
    }
    else if(!host && client != 0)
    {
        gc = new GameContext(client);
    }

    if(gc != 0)
    {
        emit play(gc);
    }
}

void LobbyMenu::showError(QAbstractSocket::SocketError err)
{
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
    emit returnToMenu();
}

void LobbyMenu::onBtConnectPressed()
{
    btConnect->setEnabled(false);
    txtAdressIP->setEnabled(false);

    if(client != 0)
    {
        delete client;
    }
    if(host)
    {
        client = new GameClient("127.0.0.1", this);
    }
    else
    {
        client = new GameClient(txtAdressIP->text(), this);
    }
    connect(client,SIGNAL(switchToGame()),this,SLOT(launchGame()));
    connect(client,SIGNAL(errorOccured(QAbstractSocket::SocketError)),
            this,SLOT(showError(QAbstractSocket::SocketError)));
    connect(client,SIGNAL(connexionOk()),this,SLOT(onSuccessfulConnexion()));
}

void LobbyMenu::onBtStartPressed()
{
    qDebug()<<"onBtStartPressed";
    client->launchGame("10.3.4/8.6.4/9.5.3/7.6.3/@6.90.-90.50.110.-1/4.0.0.30.100.2/5.180.100.10.10.-1/3.180.0.50.100.1/",
                       "10.150_30_2_1,/8./9./7./@6.50,1,-1,0/4.20,1,2,0/5.0,1,-1,0/3.50,1,1,0/");
}

void LobbyMenu::onSuccessfulConnexion()
{
    QMessageBox msgBox;
    msgBox.setText("Connextion au serveur avec succes");
    msgBox.exec();
}

void LobbyMenu::setUpUI()
{
    this->btStart = new QPushButton("Start game", this);
    this->cbbReady = new QCheckBox("Ready", this);
    this->cbxMap = new QComboBox(this);
    this->tblStatus = new QTableView(this);
    this->txtAdressIP = new QLineEdit("Enter host IP",this);
    this->btConnect = new QPushButton("Connection",this);
    this->btReturn = new QPushButton("Return",this);

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

    server = new GameServer(maxGamer,this);
    host = true;
}

void LobbyMenu::disableUI()
{
    cbxMap->setEnabled(false);
    btStart->setEnabled(false);
    cbbReady->setEnabled(false);
    btConnect->setEnabled(false);
    txtAdressIP->setEnabled(false);

    if(client != 0)
    {
        delete client;
        client = 0;
    }
    if(server != 0)
    {
        delete server;
        server = 0;
    }
}
