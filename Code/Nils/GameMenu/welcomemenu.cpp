#include "welcomemenu.h"
#include <QPushButton>
#include <QGridLayout>

WelcomeMenu::WelcomeMenu(QWidget *parent) :
    QWidget(parent)
{
    btHostGame = new QPushButton("Host", this);
    btJointGame = new QPushButton("Joint", this);
    btQuit = new QPushButton("Quit", this);

    connect(btHostGame,SIGNAL(clicked()),this,SLOT(onBtHostGamePressed()));
    connect(btJointGame,SIGNAL(clicked()),this,SLOT(onBtJointGamePressed()));
    connect(btQuit,SIGNAL(clicked()),this,SLOT(onBtQuitPressed()));

    QGridLayout *l = new QGridLayout(this);
    l->addWidget(btHostGame, 0, 0);
    l->addWidget(btJointGame, 1, 0);
    l->addWidget(btQuit, 2, 0);

    this->setLayout(l);
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
