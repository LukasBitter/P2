#include "lobbymenu.h"
#include "GameConnexion/gameclient.h"
#include "GameConnexion/gameserver.h"
#include "gamecontext.h"
#include "gamerlist.h"
#include "gamer.h"
#include "global.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

LobbyMenu::LobbyMenu(QWidget *parent) :  QWidget(parent),
    server(0), client(0), host(false)
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

    setServer(new GameServer(MAX_GAMER, this));
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
        QTableWidgetItem *l3 = new QTableWidgetItem(tr("No slot"));
        if(g->getSlotNumber() != -1)l3->setText(QString("%1").arg(g->getSlotNumber()));
        QTableWidgetItem *l4 = new QTableWidgetItem(tr("Not ready"));
        if(g->isReady())l4->setText(tr("Ready !"));

        tblStatus->setItem(cpt, 0, l1);
        tblStatus->setItem(cpt, 1, l2);
        tblStatus->setItem(cpt, 2, l3);
        tblStatus->setItem(cpt, 3, l4);
        ++cpt;
    }

    const Gamer *currentGamer = client->getCurrentGamer();
    if(currentGamer != 0)
    {
        cbtReady->setChecked(currentGamer->isReady());
        txtName->setText(QString(tr("User name : %1")).arg(currentGamer->getName()));
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
    msgBox.setText(tr("ERROR"));
    msgBox.exec();
}

void LobbyMenu::showMessage(NETWORK_INFORMATION err)
{
    QMessageBox msgBox;
    switch (err)
    {
    case I_SAME_COLOR:
        msgBox.setText(tr("Players have same color"));
        break;
    case I_SAME_SLOT:
        msgBox.setText(tr("Players have sam spawn"));
        break;
    case I_GAME_STARTED:
        msgBox.setText(tr("Game has already started"));
        break;
    case I_SLOT_NOT_SELECTED:
        msgBox.setText(tr("One player did not select any spawn"));
        break;
    case I_COLOR_NOT_SELECTED:
        msgBox.setText(tr("One player has not selected any color"));
        break;
    case I_MAP_INVALID:
        msgBox.setText(tr("Invalid map"));
        break;
    case I_MAP_NOT_BIG_ENOUGH:
        msgBox.setText(tr("Map size too small"));
        break;
    case I_NOT_READY:
        msgBox.setText(tr("One player is not ready"));
        break;
    default:
        qCritical()<<"LobbyMenu : unexpected case in 'showMessage'"<<err;
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
    text = QInputDialog::getText(this, tr("Enter user name")
                                         ,tr("User name :"), QLineEdit::Normal,
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
    txtConnected->setText("Connected");
}

void LobbyMenu::onAddMap(QString s)
{
    cbbMap->addItem(s);
}

void LobbyMenu::onCbbColorChanged(int i)
{
    if(client != 0)
        client->setColor(QColor(cbbColor->itemText(i)));
}

void LobbyMenu::onCbbSlotChanged(int i)
{
    if(client != 0)
        client->setSlot(cbbSlot->itemText(i).toInt());
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void LobbyMenu::setUpUI()
{
    //INSTANTIATION

    this->btStart = new QPushButton("Play game", this);
    this->btConnect = new QPushButton("Connection",this);
    this->btReturn = new QPushButton("Quit",this);
    this->btChangeName = new QPushButton("Change user name",this);
    this->cbtReady = new QCheckBox("Ready", this);
    this->cbbMap = new QComboBox(this);
    this->cbbColor = new QComboBox(this);
    this->cbbSlot = new QComboBox(this);
    this->tblStatus = new QTableWidget(this);
    this->txtAdressIP = new QLineEdit("Enter host IP address",this);
    this->txtName = new QLabel("Your user name : ",this);
    this->txtConnected = new QLabel("Not connected",this);

    //CONNEXION

    connect(btReturn,SIGNAL(clicked()),this,SLOT(onBtReturnPressed()));
    connect(btConnect,SIGNAL(clicked()),this,SLOT(onBtConnectPressed()));
    connect(btStart,SIGNAL(clicked()),this,SLOT(onBtStartPressed()));
    connect(cbtReady,SIGNAL(clicked()),this,SLOT(onBtReadyPressed()));
    connect(btChangeName,SIGNAL(clicked()),this,SLOT(onBtChangeNamePressed()));
    connect(cbbColor,SIGNAL(currentIndexChanged(int)),this,SLOT(onCbbColorChanged(int)));
    connect(cbbSlot,SIGNAL(currentIndexChanged(int)),this,SLOT(onCbbSlotChanged(int)));

    //PEUPLEMENT

    tblStatus->setRowCount(MAX_GAMER);
    tblStatus->setColumnCount(4);
    QStringList &s = *new QStringList();
    s<<"Nom joueur"<<"Couleur"<<"Slot spawn"<<"Pret";
    tblStatus->setHorizontalHeaderLabels(s);

    for(int i = 1; i <= MAX_GAMER; ++i)
    {
        cbbSlot->addItem(QString("%1").arg(i));
    }

    const QStringList colorNames = QColor::colorNames();
    int index = 0;
    foreach (const QString &colorName, colorNames) {
        const QColor color(colorName);
        cbbColor->addItem(colorName, color);
        const QModelIndex idx = cbbColor->model()->index(index++, 0);
        cbbColor->model()->setData(idx, color, Qt::BackgroundColorRole);
    }

    //AJOUT AU LAYOUT

    QGridLayout *l = new QGridLayout(this);
    l->addWidget(txtName, 0,0,1,2);
    l->addWidget(btChangeName, 0,2);
    l->addWidget(txtAdressIP, 1,0,1,2);
    l->addWidget(btConnect, 1,2);
    l->addWidget(tblStatus, 2,0,1,3);
    l->addWidget(cbbMap, 3,0,1,3);
    l->addWidget(cbbColor, 4,0);
    l->addWidget(cbbSlot, 4,1);
    l->addWidget(cbtReady, 4,2);

    l->addWidget(btReturn, 5,0);
    l->addWidget(txtConnected, 5,1);
    l->addWidget(btStart, 5,2);

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
