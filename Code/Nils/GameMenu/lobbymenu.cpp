#include "lobbymenu.h"
#include "GameConnexion/gameclient.h"
#include "GameConnexion/gameserver.h"
#include "gamecontext.h"
#include "gamerlist.h"
#include "gamer.h"
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
#include <QInputDialog>
#include <QLabel>
#include <QDir>


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

LobbyMenu::LobbyMenu(QWidget *parent) :  QWidget(parent),
    server(0), client(0), maxGamer(4), host(false)
{
    setUpUI();
    disableUI();
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void LobbyMenu::enableClientUI()
{
    disableUI();
    cbtReady->setEnabled(true);
    btConnect->setEnabled(true);
    txtAdressIP->setEnabled(true);

    host = false;
}

void LobbyMenu::enableServerUI()
{
    disableUI();
    cbbMap->setEnabled(true);
    btStart->setEnabled(true);
    cbtReady->setEnabled(true);

    setServer(new GameServer(maxGamer, this));
    setClient(new GameClient("127.0.0.1", this));
    host = true;
}

void LobbyMenu::updateUI()
{
    qDebug()<<"LobbyMenu : enter 'updateUI'";

    if(client == 0)return;

    tblStatus->clearContents(); //Detruit également les pointeurs
    int cpt = 0;
    foreach (Gamer *g, client->getListGamer())
    {
        QTableWidgetItem *l1 = new QTableWidgetItem(QString("%1").arg(g->getName()));
        QTableWidgetItem *l2 = new QTableWidgetItem();
        l2->setBackground(g->getColor());
        QTableWidgetItem *l3 = new QTableWidgetItem("Not ready");
        if(g->isReady())l3->setText("Ready !");

        tblStatus->setItem(cpt, 0, l1);
        tblStatus->setItem(cpt, 1, l2);
        tblStatus->setItem(cpt, 2, l3);
        ++cpt;
    }

    const Gamer *currentGamer = client->getCurrentGamer();
    if(currentGamer != 0)
    {
        cbtReady->setChecked(currentGamer->isReady());
        txtName->setText(QString("Votre pseudo : %1").arg(currentGamer->getName()));
        btChangeName->setEnabled(true);
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
        qCritical()<<"LobbyMenu : unexpected case in 'launchGame' no server and no client";
    }

    if(gc != 0)
    {
        //Perte volontaire des pinteur
        client = 0;
        server = 0;
        emit play(gc);
    }
    else
    {
        qCritical()<<"LobbyMenu : unexpected case in 'launchGame' gamecontext no created";
    }
}

void LobbyMenu::showError(QAbstractSocket::SocketError err)
{
    qWarning()<<"LobbyMenu : enter 'showError'"<<err;
    if(!host)
    {
        btConnect->setEnabled(true);
        txtAdressIP->setEnabled(true);
    }

    QMessageBox msgBox;
    msgBox.setText("ERREUR");
    msgBox.exec();
}

void LobbyMenu::showMessage(NETWORK_INFORMATION err)
{
    QMessageBox msgBox;
    switch (err)
    {
    case I_SAME_COLOR:
        msgBox.setText("Les joueurs ont la même couleur");
        break;
    case I_SAME_SLOT:
        msgBox.setText("Les joueurs ont le même spawn");
        break;
    default:
        break;
    }
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

    if(!host)
    {
        setClient(new GameClient(txtAdressIP->text(), this));
    }
    else
    {
        qCritical()<<"LobbyMenu : unexpected case in 'onBtReturnPressed'";
    }
}

void LobbyMenu::onBtStartPressed()
{
    qDebug()<<"LobbyMenu : enter 'onBtStartPressed'";
    if(client != 0)
    {
        QString map = cbbMap->currentText();
        client->launchGame(map);
    }
    else
    {
        qCritical()<<"LobbyMenu : unexpected case in 'onBtStartPressed'";
    }
}

void LobbyMenu::onBtChangeNamePressed()
{
    bool ok;
    QString text;
    text = QInputDialog::getText(this, tr("Entrez votre pseudo")
                                         ,tr("Pseudo :"), QLineEdit::Normal,
                                         "", &ok);
    if(ok)
    {
        client->setName(text);
    }
}

void LobbyMenu::onBtReadyPressed()
{
    client->setReady(cbtReady->isChecked());
}

void LobbyMenu::onSuccessfulConnexion()
{
    qDebug()<<"LobbyMenu : successfull connexion to server";
    txtConnected->setText("Connecté");
}

void LobbyMenu::onAddMap(QString &s)
{
    cbbMap->addItem(s);
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void LobbyMenu::setUpUI()
{
    this->btStart = new QPushButton("Lancer le jeu", this);
    this->cbtReady = new QCheckBox("Pret", this);
    this->cbbMap = new QComboBox(this);
    this->tblStatus = new QTableWidget(this);
    this->txtAdressIP = new QLineEdit("Entrez l'adresse IP",this);
    this->btConnect = new QPushButton("Connection",this);
    this->btReturn = new QPushButton("Retour",this);
    this->btChangeName = new QPushButton("Changer le pseudo",this);
    this->txtName = new QLabel("Votre pseudo : ",this);
    this->txtConnected = new QLabel("Non connecté",this);

    connect(btReturn,SIGNAL(clicked()),this,SLOT(onBtReturnPressed()));
    connect(btConnect,SIGNAL(clicked()),this,SLOT(onBtConnectPressed()));
    connect(btStart,SIGNAL(clicked()),this,SLOT(onBtStartPressed()));
    connect(cbtReady,SIGNAL(clicked()),this,SLOT(onBtReadyPressed()));
    connect(btChangeName,SIGNAL(clicked()),this,SLOT(onBtChangeNamePressed()));

    tblStatus->setRowCount(maxGamer);
    tblStatus->setColumnCount(3);
    QStringList &s = *new QStringList();
    s<<"Nom joueur"<<"Couleur"<<"Pret";
    tblStatus->setHorizontalHeaderLabels(s);

    QGridLayout *l = new QGridLayout(this);
    l->addWidget(txtName, 0,0,1,2);
    l->addWidget(btChangeName, 0,2);
    l->addWidget(txtAdressIP, 1,0,1,2);
    l->addWidget(btConnect, 1,2);
    l->addWidget(tblStatus, 2,0,1,3);
    l->addWidget(cbbMap, 3,0,1,3);
    l->addWidget(btReturn, 4,0);
    l->addWidget(cbtReady, 4,1);
    l->addWidget(btStart, 4,2);
    l->addWidget(txtConnected, 6,1);

    this->setLayout(l);
}

void LobbyMenu::disableUI()
{
    cbbMap->setEnabled(false);
    btStart->setEnabled(false);
    cbtReady->setEnabled(false);
    btConnect->setEnabled(false);
    txtAdressIP->setEnabled(false);
    btChangeName->setEnabled(false);
    updateUI();

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
    if(client != 0)
    {
        connect(client,SIGNAL(switchToGame()),this,SLOT(launchGame()));
        connect(client,SIGNAL(errorOccured(QAbstractSocket::SocketError)),
                this,SLOT(showError(QAbstractSocket::SocketError)));
        connect(client,SIGNAL(connexionOk()),this,SLOT(onSuccessfulConnexion()));
        connect(client,SIGNAL(updateLobby()),this,SLOT(updateUI()));
        connect(client,SIGNAL(addMapName(QString)),this,SLOT(onAddMap(QString)));
        connect(client,SIGNAL(errorOccured(NETWORK_INFORMATION)),this,SLOT(showMessage(NETWORK_INFORMATION)));
    }
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
