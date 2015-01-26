#include "gamemenumanager.h"
#include "lobbymenu.h"
#include "welcomemenu.h"
#include "gamecontext.h"
#include "editormenu.h"
#include "global.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameMenuManager::GameMenuManager(QWidget *parent) : QMainWindow(parent)
{
    setUpUI();
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void GameMenuManager::returnToMenu()
{
    qDebug()<<"GameMenuManager : want switch to welcomemenu";
    layout->setCurrentWidget(welcomemenu);
}

void GameMenuManager::goToLobbyAsHost()
{
    qDebug()<<"GameMenuManager : want switch to lobbymenu (as host)";
    lobbymenu->enableServerUI();
    layout->setCurrentWidget(lobbymenu);
}

void GameMenuManager::goToLobbyAsClient()
{
    qDebug()<<"GameMenuManager : want switch to lobbymenu (as client)";
    lobbymenu->enableClientUI();
    layout->setCurrentWidget(lobbymenu);
}

void GameMenuManager::goToGame(GameContext *gc)
{
    qDebug()<<"GameMenuManager : want switch to game";
    layout->addWidget(gc);
    layout->setCurrentWidget(gc);
}

void GameMenuManager::goToEditor()
{
    qDebug()<<"GameMenuManager : want switch to editor";
    editormenu->newView();
    layout->setCurrentWidget(editormenu);
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void GameMenuManager::setUpUI()
{
    centralWidget = new QWidget(this);
    layout = new QStackedLayout(centralWidget);

    //PARAMETRAGE

    setFixedSize(820,620);

    //INSTANTIATION

    welcomemenu = new WelcomeMenu(this);
    editormenu = new EditorMenu(this);
    lobbymenu = new LobbyMenu(this);

    //CONNEXION

    connect(welcomemenu,SIGNAL(btHostGamePressed()),this,SLOT(goToLobbyAsHost()));
    connect(welcomemenu,SIGNAL(btJointGamePressed()),this,SLOT(goToLobbyAsClient()));
    connect(welcomemenu,SIGNAL(btEditorPressed()),this,SLOT(goToEditor()));
    connect(welcomemenu,SIGNAL(btQuitPressed()),this,SLOT(close()));
    connect(lobbymenu,SIGNAL(returnToMenu()),this,SLOT(returnToMenu()));
    connect(lobbymenu,SIGNAL(play(GameContext*)),this,SLOT(goToGame(GameContext*)));

    //AJOUT LAYOUT

    layout->addWidget(welcomemenu);
    layout->addWidget(editormenu);
    layout->addWidget(lobbymenu);

    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);
}

