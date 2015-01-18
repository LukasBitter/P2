#include "gamemenumanager.h"
#include "lobbymenu.h"
#include "welcomemenu.h"
#include "gamecontext.h"
#include <QStackedLayout>

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameMenuManager::GameMenuManager(QWidget *parent) : QMainWindow(parent)
{
    setUpUI();

    //Connexion
    connect(welcomemenu,SIGNAL(btHostGamePressed()),this,SLOT(goToLobbyAsHost()));
    connect(welcomemenu,SIGNAL(btJointGamePressed()),this,SLOT(goToLobbyAsClient()));
    connect(welcomemenu,SIGNAL(btQuitPressed()),this,SLOT(close()));
    connect(lobbymenu,SIGNAL(returnToMenu()),this,SLOT(returnToMenu()));
    connect(lobbymenu,SIGNAL(play(GameContext*)),this,SLOT(goToGame(GameContext*)));
}

GameMenuManager::~GameMenuManager()
{
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void GameMenuManager::returnToMenu()
{
    layout->setCurrentWidget(welcomemenu);
}

void GameMenuManager::goToLobbyAsHost()
{
    lobbymenu->enableServerUI();
    layout->setCurrentWidget(lobbymenu);
}

void GameMenuManager::goToLobbyAsClient()
{
    lobbymenu->enableClientUI();
    layout->setCurrentWidget(lobbymenu);
}

void GameMenuManager::goToGame(GameContext *gc)
{
    layout->addWidget(gc);
    layout->setCurrentWidget(gc);
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void GameMenuManager::setUpUI()
{
    centralWidget = new QWidget(this);
    layout = new QStackedLayout(centralWidget);

    //Proprieté de la fenetre
    setFixedSize(800,600);

    //Composant
    welcomemenu = new WelcomeMenu(this);
    lobbymenu = new LobbyMenu(this);


    layout->addWidget(welcomemenu);
    layout->addWidget(lobbymenu);

    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);
}

