#include "welcomemenu.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

WelcomeMenu::WelcomeMenu(QWidget *parent) :
    QWidget(parent)
{
    setUpUI();
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void WelcomeMenu::onBtEditorPressed()
{
    emit btEditorPressed();
}

void WelcomeMenu::onBtHostGamePressed()
{
    emit btHostGamePressed();
}

void WelcomeMenu::onBtJointGamePressed()
{
    emit btJointGamePressed();
}

void WelcomeMenu::onBtQuitPressed()
{
    emit btQuitPressed();
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void WelcomeMenu::setUpUI()
{
    //INSTANTIATION

    btHostGame = new QPushButton(tr("Host"), this);
    btJointGame = new QPushButton(tr("Join"), this);
    btQuit = new QPushButton(tr("Quit"), this);
    btEditor = new QPushButton(tr("Editor"), this);

    //CONNEXION

    connect(btHostGame,SIGNAL(clicked()),this,SLOT(onBtHostGamePressed()));
    connect(btJointGame,SIGNAL(clicked()),this,SLOT(onBtJointGamePressed()));
    connect(btQuit,SIGNAL(clicked()),this,SLOT(onBtQuitPressed()));
    connect(btEditor,SIGNAL(clicked()),this,SLOT(onBtEditorPressed()));

    //AJOUT LAYOUT

    QGridLayout *l = new QGridLayout(this);
    l->addWidget(btEditor, 1, 0);
    l->addWidget(btHostGame, 2, 0);
    l->addWidget(btJointGame, 5, 0);
    l->addWidget(btQuit, 10, 0);
    l->setAlignment(Qt::AlignCenter);

    this->setLayout(l);
}
