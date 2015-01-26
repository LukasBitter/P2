#include "lobbymenu.h"
#include "gamer.h"
#include "GameConnexion/gameclient.h"
#include "GameConnexion/gameserver.h"


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

    tblStatus->clearContents(); //Detruit également les pointeurs

    if(client == 0)return;

    int cpt = 0;
    foreach (Gamer *g, client->getListGamer())
    {
        QTableWidgetItem *l1 = new QTableWidgetItem(QString("%1").arg(g->getName()));
        QTableWidgetItem *l2 = new QTableWidgetItem();
        l2->setBackground(g->getColor());
        QTableWidgetItem *l3 = new QTableWidgetItem("No slot");
        if(g->getSlotNumber() != -1)l3->setText(QString("%1").arg(g->getSlotNumber()));
        QTableWidgetItem *l4 = new QTableWidgetItem("Not ready");
        if(g->isReady())l4->setText("Ready !");

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
        txtName->setText(QString("Votre pseudo : %1").arg(currentGamer->getName()));
        btChangeName->setEnabled(true);
        cbbColor->setCurrentIndex(cbbColor->findData(currentGamer->getColor()));
        cbbSlot->setCurrentIndex(cbbSlot->findData(currentGamer->getSlotNumber()));

    }
}

void LobbyMenu::orderToSwitchToGame()
{
    qDebug()<<"LobbyMenu : enter 'launchGame'";

    if(client != 0)
    {
        emit play(client->getMap());
    }
    else
    {
        qCritical()<<"LobbyMenu : unexpected case in 'launchGame' no server and no client";
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
    case I_GAME_STARTED:
        msgBox.setText("La partie est deja commencée");
        break;
    case I_SLOT_NOT_SELECTED:
        msgBox.setText("Un joueur n'a pas selectionné de spawn");
        break;
    case I_COLOR_NOT_SELECTED:
        msgBox.setText("Un joueur n'a pas selectionné de couleur");
        break;
    case I_MAP_INVALID:
        msgBox.setText("La map est invalide");
        break;
    case I_MAP_NOT_BIG_ENOUGH:
        msgBox.setText("La map n'est pas assez grande");
        break;
    case I_NOT_READY:
        msgBox.setText("Un joueur n'est pas prêt");
        break;
    case I_LOBBY_FULL:
        msgBox.setText("Le salon est plein");
        break;
    default:
        qCritical()<<"LobbyMenu : unexpected case in 'showMessage'"<<err;
        break;
    }
    msgBox.exec();
}

void LobbyMenu::wantReturnToMenu()
{
    qDebug()<<"LobbyMenu : want switch to menu";
    emit returnToMenu();
}

void LobbyMenu::wantConnectToServer()
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

void LobbyMenu::wantLaunchGame()
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

void LobbyMenu::wantChangeName()
{
    bool stop = false;

    while(!stop)
    {
        QString previousName = client->getCurrentGamer()->getName();
        bool ok = false;
        QString currentName = QInputDialog::getText(this, tr("Entrez votre pseudo")
                                                    ,tr("Pseudo :"), QLineEdit::Normal,
                                                    "", &ok);

        if(ok && !currentName.isEmpty())
        {
            stop = client->setName(currentName);

            if(!stop)
            {
                QMessageBox msgBox;
                msgBox.setText("Contient des caractaires interdits");
                msgBox.exec();
            }
            else
            {
                client->sendChatMessage(previousName+" --> "+currentName);
            }
        }
        else if(!ok && !previousName.isEmpty())
        {
            stop = true;
        }
    }
}

void LobbyMenu::wantChangeReadyState()
{
    client->setReady(cbtReady->isChecked());
}

void LobbyMenu::wantSendChatMessage()
{
    if(client != 0 && !txtToSendChat->text().isEmpty())
    {
        client->sendChatMessage(txtToSendChat->text());
        txtToSendChat->setText("");
    }
}

void LobbyMenu::onSuccessfulConnexion()
{
    qDebug()<<"LobbyMenu : successfull connexion to server";
    txtConnected->setText("Connecté");
    wantChangeName();
}

void LobbyMenu::onAddMap(QString s)
{
    cbbMap->addItem(s);
}

void LobbyMenu::onCbbColorChanged(int i)
{
    if(client != 0)
    {
        client->setColor(cbbColor->itemData(i).value<QColor>());
    }
}

void LobbyMenu::onCbbSlotChanged(int i)
{
    if(client != 0)
        client->setSlot(cbbSlot->itemText(i).toInt());
}

void LobbyMenu::onReciveChatMessage(QString s)
{
    txtChat->append(s);
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void LobbyMenu::setUpUI()
{
    //INSTANTIATION

    this->btStart = new QPushButton("Lancer le jeu", this);
    this->btConnect = new QPushButton("Connection",this);
    this->btReturn = new QPushButton("Retour",this);
    this->btChangeName = new QPushButton("Changer le pseudo",this);
    this->cbtReady = new QCheckBox("Pret", this);
    this->cbbMap = new QComboBox(this);
    this->cbbColor = new QComboBox(this);
    this->cbbSlot = new QComboBox(this);
    this->tblStatus = new QTableWidget(this);
    this->txtAdressIP = new QLineEdit("Entrez l'adresse IP",this);
    this->txtName = new QLabel("Votre pseudo : ",this);
    this->txtConnected = new QLabel("Non connecté",this);
    this->txtChat = new QTextEdit(this);
    this->txtToSendChat = new QLineEdit(this);
    this->btSend = new QPushButton("Envoyer", this);

    //CONNEXION

    connect(btSend,SIGNAL(clicked()),this,SLOT(wantSendChatMessage()));
    connect(txtToSendChat,SIGNAL(returnPressed()),this,SLOT(wantSendChatMessage()));
    connect(btReturn,SIGNAL(clicked()),this,SLOT(wantReturnToMenu()));
    connect(btConnect,SIGNAL(clicked()),this,SLOT(wantConnectToServer()));
    connect(txtAdressIP,SIGNAL(returnPressed()),this,SLOT(wantConnectToServer()));
    connect(btStart,SIGNAL(clicked()),this,SLOT(wantLaunchGame()));
    connect(cbtReady,SIGNAL(clicked()),this,SLOT(wantChangeReadyState()));
    connect(btChangeName,SIGNAL(clicked()),this,SLOT(wantChangeName()));
    connect(cbbColor,SIGNAL(currentIndexChanged(int)),this,SLOT(onCbbColorChanged(int)));
    connect(cbbSlot,SIGNAL(currentIndexChanged(int)),this,SLOT(onCbbSlotChanged(int)));

    //PARAMETRAGE

    tblStatus->setRowCount(MAX_GAMER);
    tblStatus->setColumnCount(4);
    QStringList &s = *new QStringList();
    s<<"Nom joueur"<<"Couleur"<<"Slot spawn"<<"Pret";
    tblStatus->setHorizontalHeaderLabels(s);
    tblStatus->verticalHeader()->setVisible(false);
    txtChat->setReadOnly(true);


    //PEUPLEMENT

    populate();

    //AJOUT AU LAYOUT

    QGridLayout *l = new QGridLayout(this);
    l->setColumnStretch(0, 1);
    l->setColumnStretch(1, 1);
    l->setColumnStretch(2, 1);
    l->addWidget(txtName, 0,0,1,2);
    l->addWidget(btChangeName, 0,2);
    l->addWidget(txtAdressIP, 1,0,1,2);
    l->addWidget(btConnect, 1,2);
    l->addWidget(tblStatus, 10,0,3,2);
    l->addWidget(txtChat, 10,2);
    l->addWidget(txtToSendChat, 11,2);
    l->addWidget(btSend, 12,2);
    l->addWidget(cbbMap, 20,0,1,3);
    l->addWidget(cbbColor, 21,0);
    l->addWidget(cbbSlot, 21,1);
    l->addWidget(cbtReady, 21,2);

    l->addWidget(btReturn, 30,0);
    l->addWidget(txtConnected, 30,1);
    l->addWidget(btStart, 30,2);

    this->setLayout(l);
}

void LobbyMenu::populate()
{
    //Tableau des couleurs de joueur
    QColor colorArray [MAX_GAMER] = PLAYER_COLOR;

    //peuplement du combobox de selection de slot
    for(int i = 1; i <= MAX_GAMER; ++i)
    {
        cbbSlot->addItem(QString("%1").arg(i), i);
    }

    //Peuplement du combobox de selection de la couleur
    cbbColor->addItem("Rouge", colorArray[0]);
    cbbColor->addItem("Vert", colorArray[1]);
    cbbColor->addItem("Orange", colorArray[2]);
    cbbColor->addItem("Jaune", colorArray[3]);
}

void LobbyMenu::disableUI()
{
    setClient(0);
    setServer(0);

    cbbMap->setEnabled(false);
    btStart->setEnabled(false);
    cbtReady->setEnabled(false);
    btConnect->setEnabled(false);
    txtAdressIP->setEnabled(false);
    btChangeName->setEnabled(false);

    txtAdressIP->setText("Entrez l'adresse IP");
    txtName->setText("Votre pseudo : ");

    updateUI();
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
        connect(client,SIGNAL(switchToGame()),this,SLOT(orderToSwitchToGame()));
        connect(client,SIGNAL(errorOccured(QAbstractSocket::SocketError)),
                this,SLOT(showError(QAbstractSocket::SocketError)));
        connect(client,SIGNAL(connexionOk()),this,SLOT(onSuccessfulConnexion()));
        connect(client,SIGNAL(updateLobby()),this,SLOT(updateUI()));
        connect(client,SIGNAL(addMapName(QString)),this,SLOT(onAddMap(QString)));
        connect(client,SIGNAL(errorOccured(NETWORK_INFORMATION)),this,SLOT(showMessage(NETWORK_INFORMATION)));
        connect(client,SIGNAL(reciveChatMessage(QString)),this,SLOT(onReciveChatMessage(QString)));
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
