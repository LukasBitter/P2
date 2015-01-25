#include "gamemenumanager.h"
#include "lobbymenu.h"
#include "welcomemenu.h"
#include "endgamemenu.h"
#include "global.h"
#include "GameComponent/gameview.h"
#include "GameComponent/editview.h"


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

void GameMenuManager::goToGame(GameView *w)
{
    qDebug()<<"GameMenuManager : want switch to game";
    connect(w,SIGNAL(returnToMenu()),this,SLOT(returnToMenu()));
    connect(w,SIGNAL(gameFinish(bool)),this,SLOT(gameFinished(bool)));
    layout->addWidget(w);
    layout->setCurrentWidget(w);
}

void GameMenuManager::goToEditor()
{
    qDebug()<<"GameMenuManager : want switch to editor";
    layout->setCurrentWidget(editormenu);
}

void GameMenuManager::gameFinished(bool victory)
{
    qDebug()<<"GameMenuManager : game is finished";
    if(victory)
    {
        qDebug()<<"GameMenuManager : want switch to end menu (for victory)";
        endgamemenu->enableVictory();
        layout->setCurrentWidget(endgamemenu);
    }
    else
    {
        qDebug()<<"GameMenuManager : want switch to end menu (for defeat)";
        endgamemenu->enableDefeat();
        layout->setCurrentWidget(endgamemenu);
    }
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
    editormenu = new EditView(this);
    lobbymenu = new LobbyMenu(this);
    endgamemenu = new EndGameMenu(this);

    //CONNEXION

    connect(welcomemenu,SIGNAL(btHostGamePressed()),this,SLOT(goToLobbyAsHost()));
    connect(welcomemenu,SIGNAL(btJointGamePressed()),this,SLOT(goToLobbyAsClient()));
    connect(welcomemenu,SIGNAL(btEditorPressed()),this,SLOT(goToEditor()));
    connect(welcomemenu,SIGNAL(btQuitPressed()),this,SLOT(close()));
    connect(lobbymenu,SIGNAL(returnToMenu()),this,SLOT(returnToMenu()));
    connect(editormenu,SIGNAL(returnToMenu()),this,SLOT(returnToMenu()));
    connect(endgamemenu,SIGNAL(returnToMenu()),this,SLOT(returnToMenu()));
    connect(lobbymenu,SIGNAL(play(GameView*)),this,SLOT(goToGame(GameView*)));

    //AJOUT LAYOUT

    layout->addWidget(welcomemenu);
    layout->addWidget(editormenu);
    layout->addWidget(lobbymenu);
    layout->addWidget(endgamemenu);

    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);
}

