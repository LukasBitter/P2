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
/*SURCHARGE*/
/*----------------------------------------------------*/

void EditorInterface::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRectF target(-15.0, -15.0, 840.0, 580.0);
    QRectF source(0.0, 0.0, 2975.0, 1870.0);

    painter.drawPixmap(target, background, source);
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

bool EditorInterface::isStandardNodeChecked() const
{
    return rbtStandard->isChecked();
}

bool EditorInterface::isSpawnNodeChecked() const
{
    return rbtSpawn->isChecked();
}

bool EditorInterface::isManaNodeChecked() const
{
    return rbtMana->isChecked();
}

int EditorInterface::getNodeSize() const
{
    return spSize->value();
}

int EditorInterface::getNodeRessource() const
{
    return spRessource->value();
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

void EditorInterface::onBtClearPressed()
{
    emit btClearPressed();
}

/*----------------------------------------------------*/
/*PRIVATE*/
/*----------------------------------------------------*/

void EditorInterface::setUpUI()
{
    //INSTANTIATION

    spRessource = new QSpinBox(this);
    spSize = new QSpinBox(this);
    rbtStandard = new QRadioButton("Standard node", this);
    rbtSpawn = new QRadioButton("Spawn node", this);
    rbtMana = new QRadioButton("Mana node", this);
    btCreateNode = new QPushButton("Create node", this);
    btRemoveNode = new QPushButton("Delete node", this);
    btConnectNode = new QPushButton("Connect node", this);
    btDisconnectNode = new QPushButton("Disconnect node", this);
    btReturn = new QPushButton("Retour", this);
    btLoadFromFile = new QPushButton("Ouvrir", this);
    btSaveToFile = new QPushButton("Sauver", this);
    btClear = new QPushButton("Clear", this);

    //PARAMETRAGE

    spRessource->setMaximum(150);
    spRessource->setMinimum(0);
    spSize->setMaximum(3);
    spSize->setMinimum(1);
    rbtStandard->setChecked(true);
    background.load(":/ButtonBackground.png");

    //CONNEXION

    connect(btCreateNode, SIGNAL(pressed()), this, SLOT(onBtCreateNodePressed()));
    connect(btRemoveNode, SIGNAL(pressed()), this, SLOT(onBtRemoveNodePressed()));
    connect(btConnectNode, SIGNAL(pressed()), this, SLOT(onBtConnectNodePressed()));
    connect(btDisconnectNode, SIGNAL(pressed()), this, SLOT(onBtDisconnectNodePressed()));
    connect(btReturn, SIGNAL(pressed()), this, SLOT(onBtReturnPressed()));
    connect(btLoadFromFile, SIGNAL(pressed()), this, SLOT(onBtLoadFromFilePressed()));
    connect(btSaveToFile, SIGNAL(pressed()), this, SLOT(onBtSaveToFilePressed()));
    connect(btClear, SIGNAL(pressed()), this, SLOT(onBtClearPressed()));

    //AJOUT AU LAYOUT

    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(new QLabel("Node size", this), 0,0);
    layout->addWidget(spSize, 1,0);
    layout->addWidget(new QLabel("Initial ressource", this), 2,0);
    layout->addWidget(spRessource, 3,0);
    layout->addWidget(rbtStandard, 4,0);
    layout->addWidget(rbtSpawn, 5,0);
    layout->addWidget(rbtMana, 6,0);
    layout->addWidget(btCreateNode, 10,0);
    layout->addWidget(btRemoveNode, 11,0);
    layout->addWidget(btConnectNode, 12,0);
    layout->addWidget(btDisconnectNode, 13,0);
    layout->addWidget(new QLabel("Open / save", this), 20,0);
    layout->addWidget(btLoadFromFile, 21,0);
    layout->addWidget(btSaveToFile, 22,0);
    layout->addWidget(btClear, 23,0);
    layout->addWidget(btReturn, 24,0);

    this->setLayout(layout);

}
