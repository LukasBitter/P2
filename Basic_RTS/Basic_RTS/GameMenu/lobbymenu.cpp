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
/*SURCHARGE*/
/*----------------------------------------------------*/

void LobbyMenu::paintEvent(QPaintEvent *)
{
    // AJOUT BACKGROUND

    background.load(":/Background.png");

    QPainter painter(this);
    QRectF target(0.0, 0.0, 1280.0, 800.0);
    QRectF source(0.0, 0.0, 1280.0, 800.0);

    painter.drawPixmap(target, background, source);
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
        txtName->setText(QString(tr("Your user name: %1")).arg(currentGamer->getName()));
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
    msgBox.setText(tr("ERROR"));
    msgBox.exec();
}

void LobbyMenu::showMessage(NETWORK_INFORMATION err)
{
    QMessageBox msgBox;
    switch (err)
    {
    case I_SAME_COLOR:
        msgBox.setText(tr("Players have the same colour"));
        break;
    case I_SAME_SLOT:
        msgBox.setText(tr("Players have same spawn"));
        break;
    case I_GAME_STARTED:
        msgBox.setText(tr("Game is already running"));
        break;
    case I_SLOT_NOT_SELECTED:
        msgBox.setText(tr("A player hasn't selected any spawn"));
        break;
    case I_COLOR_NOT_SELECTED:
        msgBox.setText(tr("A player hasn't selected any colour"));
        break;
    case I_MAP_INVALID:
        msgBox.setText(tr("Invalid map"));
        break;
    case I_MAP_NOT_BIG_ENOUGH:
        msgBox.setText(tr("Map is too small"));
        break;
    case I_NOT_READY:
        msgBox.setText(tr("A player is not ready"));
        break;
    case I_LOBBY_FULL:
        msgBox.setText(tr("Lobby is full!"));
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
        QString currentName = QInputDialog::getText(this, tr("Enter your user name")
                                                    ,tr("User name :"), QLineEdit::Normal,
                                                    "", &ok);

        if(ok && !currentName.isEmpty())
        {
            stop = client->setName(currentName);

            if(!stop)
            {
                QMessageBox msgBox;
                msgBox.setText(tr("Contains invalid characters"));
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

    txtConnected->setText(tr("Connected"));
    wantChangeName(); //Demande un nom  au démmarage
    if(host) client->setReady(true); //Le joueur host est pret de base
}

void LobbyMenu::onAddMap(QString s)
{
    cbbMap->addItem(s);
}

void LobbyMenu::onMapChangeFromServer(QString s)
{
    cbbMap->setCurrentIndex(cbbMap->findText(s));
}

void LobbyMenu::onCbbMapChanged(int i)
{
    if(client != 0 && host)
    {
        client->setMap(i);
    }
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

    this->btStart = new QPushButton(tr("&Launch game"), this);
    this->btConnect = new QPushButton(tr("&Connection"),this);
    this->btReturn = new QPushButton(tr("&Back"),this);
    this->btChangeName = new QPushButton(tr("Change &user name"),this);
    this->cbtReady = new QCheckBox(tr("&Ready"), this);
    this->cbbMap = new QComboBox(this);
    this->cbbColor = new QComboBox(this);
    this->cbbSlot = new QComboBox(this);
    this->tblStatus = new QTableWidget(this);
    this->txtLobby = new QLabel(tr("<h2>Welcome in the lobby</h2>"), this);
    this->txtAdressIP = new QLineEdit(tr("&Host IP address"),this);
    this->txtName = new QLabel(tr("Your user name : "),this);
    this->txtUserList = new QLabel(tr("Connected users : "),this);
    this->txtMap = new QLabel(tr("Map : "),this);
    this->txtColour = new QLabel(tr("Player colour : "),this);
    this->txtSlotSpawn = new QLabel(tr("Slot spawn : "),this);
    this->txtStatus = new QLabel(tr("Status : "),this);
    this->txtConnected = new QLabel(tr("Not connected"),this);
    this->txtChat = new QTextEdit(this);
    this->txtToSendChat = new QLineEdit(this);
    this->btSend = new QPushButton(tr("&Send"), this);

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
    connect(cbbMap,SIGNAL(currentIndexChanged(int)),this,SLOT(onCbbMapChanged(int)));

    //PARAMETRAGE

    tblStatus->setRowCount(MAX_GAMER);
    tblStatus->setColumnCount(4);
    QStringList &s = *new QStringList();
    s<<tr("Player name")<<tr("Colour")<<tr("Slot spawn")<<tr("Ready");
    tblStatus->setHorizontalHeaderLabels(s);
    tblStatus->verticalHeader()->setVisible(false);
    tblStatus->setMaximumHeight(145);
    tblStatus->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tblStatus->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    txtChat->setReadOnly(true);
    this->setStyleSheet("QLabel { color: white}");
    txtLobby->setStyleSheet("color: white; font-size: 16px;");


    //PEUPLEMENT

    populate();

    //AJOUT AU LAYOUT

    QGridLayout *l = new QGridLayout(this);
    l->setColumnStretch(0, 1);
    l->setColumnStretch(1, 1);
    l->setColumnStretch(2, 1);
    l->setColumnStretch(3, 1);
    l->setColumnStretch(4, 3);
    l->addWidget(txtLobby, 0, 1, 1, 3);
    l->addWidget(txtName, 1,0, 1, 2);
    l->addWidget(btChangeName, 1,2);
    l->addWidget(txtAdressIP, 2,0);
    l->addWidget(btConnect, 2,1);
    l->addWidget(txtUserList, 3,0);
    l->addWidget(tblStatus, 4,0,6,4);
    l->addWidget(txtMap, 10,0, 1, 1, Qt::AlignRight);
    l->addWidget(cbbMap, 10,1, 1, 2);
    l->addWidget(txtColour, 11,0, 1, 1, Qt::AlignRight);
    l->addWidget(cbbColor, 11,1);
    l->addWidget(txtSlotSpawn, 12,0, 1, 1, Qt::AlignRight);
    l->addWidget(cbbSlot, 12,1);
    l->addWidget(txtStatus, 13,0, 1, 1, Qt::AlignRight);
    l->addWidget(txtConnected, 13,1);
    l->addWidget(cbtReady, 14,1);
    l->addWidget(txtChat, 1,4, 20, 1);
    l->addWidget(txtToSendChat, 21,4);
    l->addWidget(btSend, 22,4);

    l->addWidget(btReturn, 16,1);
    l->addWidget(btStart, 16,2);

    this->setLayout(l);
    txtToSendChat->setFocus();

    // TAB ORDER
    setTabOrder(txtAdressIP, btConnect);
    setTabOrder(btConnect, cbbMap);
    setTabOrder(cbbMap, cbbColor);
    setTabOrder(cbbColor, cbbSlot);
    setTabOrder(cbbSlot, cbtReady);
    setTabOrder(cbtReady, btStart);
    setTabOrder(btStart, btReturn);
    setTabOrder(btReturn, txtToSendChat);
    setTabOrder(txtToSendChat, btSend);
    setTabOrder(btSend, btChangeName);
    setTabOrder(btChangeName, txtAdressIP);
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
    cbbColor->addItem(tr("Red"), colorArray[0]);
    cbbColor->addItem(tr("Green"), colorArray[1]);
    cbbColor->addItem(tr("Orange"), colorArray[2]);
    cbbColor->addItem(tr("Yellow"), colorArray[3]);
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

    txtAdressIP->setText(tr("Host IP address"));
    txtName->setText(tr("Your user name : "));

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
        connect(client,SIGNAL(mapSelectionChange(QString)),this,SLOT(onMapChangeFromServer(QString)));
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
