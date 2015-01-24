#include "editorinterface.h"
#include "GameComponent/GameInterface/button.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

EditorInterface::EditorInterface(QWidget *parent) : QWidget(parent)
{
    setUpUI();
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void EditorInterface::onBtCreateNodePressed()
{
    emit btActionPressed(EA_ADD);
}

void EditorInterface::onBtRemoveNodePressed()
{
    emit btActionPressed(EA_REMOVE);
}

void EditorInterface::onBtConnectNodePressed()
{
    emit btActionPressed(EA_CONNECT);
}

void EditorInterface::onBtDisconnectNodePressed()
{
    emit btActionPressed(EA_DISCONNECT);
}

void EditorInterface::onBtSaveToFilePressed()
{
    emit btSaveToFilePressed();
}

void EditorInterface::onBtLoadFromFilePressed()
{
    emit btLoadFromFilePressed();
}

void EditorInterface::onBtReturnPressed()
{
    emit btReturnPressed();
}

/*----------------------------------------------------*/
/*PRIVATE*/
/*----------------------------------------------------*/

void EditorInterface::setUpUI()
{
    //INSTANTIATION

    btCreateNode = new QPushButton("Create node", this);
    btRemoveNode = new QPushButton("Delete node", this);
    btConnectNode = new QPushButton("Connect node", this);
    btDisconnectNode = new QPushButton("Disconnect node", this);
    btReturn = new QPushButton("Retour", this);
    btLoadFromFile = new QPushButton("Ouvrir", this);
    btSaveToFile = new QPushButton("Sauver", this);

    //CONNEXION

    connect(btCreateNode, SIGNAL(pressed()), this, SLOT(onBtCreateNodePressed()));
    connect(btRemoveNode, SIGNAL(pressed()), this, SLOT(onBtRemoveNodePressed()));
    connect(btConnectNode, SIGNAL(pressed()), this, SLOT(onBtConnectNodePressed()));
    connect(btDisconnectNode, SIGNAL(pressed()), this, SLOT(onBtDisconnectNodePressed()));
    connect(btReturn, SIGNAL(pressed()), this, SLOT(onBtReturnPressed()));
    connect(btLoadFromFile, SIGNAL(pressed()), this, SLOT(onBtLoadFromFilePressed()));
    connect(btSaveToFile, SIGNAL(pressed()), this, SLOT(onBtSaveToFilePressed()));

    //AJOUT AU LAYOUT

    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(btCreateNode, 0,0);
    layout->addWidget(btRemoveNode, 1,0);
    layout->addWidget(btConnectNode, 2,0);
    layout->addWidget(btDisconnectNode, 3,0);
    layout->addWidget(btLoadFromFile, 4,0);
    layout->addWidget(btSaveToFile, 5,0);
    layout->addWidget(btReturn, 6,0);

    this->setLayout(layout);

}
