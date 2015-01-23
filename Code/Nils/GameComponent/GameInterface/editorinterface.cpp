#include "editorinterface.h"
#include "GameComponent/GameInterface/button.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

EditorInterface::EditorInterface(QGraphicsItem * parent) : QGraphicsWidget(parent)
{
    setUpUI();
}

QRectF EditorInterface::boundingRect() const
{

}

void EditorInterface::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

/*----------------------------------------------------*/
/*PRIVATE*/
/*----------------------------------------------------*/

void EditorInterface::setUpUI()
{
    //INSTANTIATION

    btCreateNode = new Button("Create node", this);
    btRemoveNode = new Button("Delete node", this);
    btConnectNode = new Button("Connect node", this);
    btDisconnectNode = new Button("Disconnect node", this);

    //CONNEXION

    connect(btCreateNode, SIGNAL(pressed()), this, SLOT(onBtCreateNodePressed()));
    connect(btRemoveNode, SIGNAL(pressed()), this, SLOT(onBtRemoveNodePressed()));
    connect(btConnectNode, SIGNAL(pressed()), this, SLOT(onBtConnectNodePressed()));
    connect(btDisconnectNode, SIGNAL(pressed()), this, SLOT(onBtDisconnectNodePressed()));

    //POSITIONNEMENT

    btCreateNode->setX(25);
    btRemoveNode->setX(25);
    btConnectNode->setX(25);
    btDisconnectNode->setX(25);
    btCreateNode->setY(25);
    btRemoveNode->setY(70);
    btConnectNode->setY(115);
    btDisconnectNode->setY(160);
}
