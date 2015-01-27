#include "powerinterface.h"
#include "actionmanager.h"
#include "progressbar.h"
#include "GameComponent/Logic/node.h"
#include "GameComponent/GameInterface/button.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

PowerInterface::PowerInterface(ActionManager &am, QGraphicsItem * parent) :
    QGraphicsWidget(parent),mana(0), powerSelected(NO_POWER),
    am(am)
{
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setUpUI();
    startTimer(POWER_TIC);
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

QRectF PowerInterface::boundingRect() const
{
    return QRectF(0, 0, 120, 280);
}

void PowerInterface::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPixmap buttonBackground(":/ButtonBackground.png");

    QRectF source(0, 0, 502, 1446);
    painter->drawPixmap(boundingRect(), buttonBackground, source);
}

void PowerInterface::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    pcd.advence();

    btPowerArmore->setPowerPercent(pcd.percentReload(GA_USEPOWER_ARMORE));
    btPowerInvincibility->setPowerPercent(pcd.percentReload(GA_USEPOWER_INVINCIBILITY));
    btPowerTeleportation->setPowerPercent(pcd.percentReload(GA_USEPOWER_TELEPORTATION));
    btPowerDestroy->setPowerPercent(pcd.percentReload(GA_USEPOWER_DESTROY));

    btPowerArmore->setSelected(am.getCurrentAction() == GA_USEPOWER_ARMORE);
    btPowerInvincibility->setSelected(am.getCurrentAction() == GA_USEPOWER_INVINCIBILITY);
    btPowerTeleportation->setSelected(am.getCurrentAction() == GA_USEPOWER_TELEPORTATION);
    btPowerDestroy->setSelected(am.getCurrentAction() == GA_USEPOWER_DESTROY);

    pbMana->setValue(0, mana);
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

void PowerInterface::setMana(int mana)
{
    if(mana > 0)this->mana = mana;
    if(this->mana > P_MAX_MANA)this->mana = P_MAX_MANA;
}

void PowerInterface::addMana(int mana)
{
    if(mana > 0)this->mana += mana;
    if(this->mana > P_MAX_MANA)this->mana = P_MAX_MANA;
}

int PowerInterface::getMana() const
{
    return mana;
}

const PowerCountDown &PowerInterface::getCountDownManager() const
{
    return pcd;
}

/*----------------------------------------------------*/
/*SIGNAL/SLOT*/
/*----------------------------------------------------*/

void PowerInterface::shortCutPressed(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_1:
    {
        btPowerDestroyPressed();
        break;
    }
    case Qt::Key_2:
    {
        btPowerInvincibilityPressed();
        break;
    }
    case Qt::Key_3:
    {
        btPowerTeleportationPressed();
        break;
    }
    case Qt::Key_4:
    {
        btPowerArmorePressed();
        break;
    }
    default:
        break;
    }
}

void PowerInterface::usePower(ACTIONS a, Node *n1, Node *n2)
{
    if(!pcd.isReady(a)) return;

    int cost = 0;
    int countDownTime = 0;
    int powerDuration = 0;

    switch (a)
    {
    case GA_USEPOWER_DESTROY:
    {
        cost = P_DESTROY_COST;
        countDownTime = P_DESTROY_CD;
        powerDuration = 0;
        break;
    }
    case GA_USEPOWER_INVINCIBILITY:
    {
        cost = P_INVINCIBILITY_COST;
        countDownTime = P_INVINCIBILITY_CD;
        powerDuration = P_INVINCIBILITY_DURATION;
        break;
    }
    case GA_USEPOWER_TELEPORTATION:
    {
        cost = P_TELEPORTATION_COST;
        countDownTime = P_TELEPORTATION_CD;
        powerDuration = 0;
        break;
    }
    case GA_USEPOWER_ARMORE:
    {
        countDownTime = P_ARMOR_CD;
        powerDuration = P_ARMOR_DURATION;
        cost = P_ARMOR_COST;
        break;
    }
    default:
        break;
    }

    if(mana >= cost)
    {
        mana -= cost;
        pcd.addCountDown(countDownTime, powerDuration, a, n1, n2);
    }
}


void PowerInterface::btPowerArmorePressed()
{
    am.actionChanged(GA_USEPOWER_ARMORE);
}

void PowerInterface::btPowerInvincibilityPressed()
{
    am.actionChanged(GA_USEPOWER_INVINCIBILITY);
}

void PowerInterface::btPowerTeleportationPressed()
{
    am.actionChanged(GA_USEPOWER_TELEPORTATION);
}

void PowerInterface::btPowerDestroyPressed()
{
    am.actionChanged(GA_USEPOWER_DESTROY);
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void PowerInterface::setUpUI()
{
    //INSTANTIATION
    btPowerArmore = new Button(ARMOR, this);
    btPowerInvincibility = new Button(INVINCIBILITY, this);
    btPowerTeleportation = new Button(TELEPORTATION, this);
    btPowerDestroy = new Button(DESTRUCTION, this);
    pbMana = new ProgressBar(QRectF(25, 25, 6, 230), this);

    //CONNEXION

    connect(btPowerDestroy, SIGNAL(pressed()), this, SLOT(btPowerDestroyPressed()));
    connect(btPowerInvincibility, SIGNAL(pressed()), this, SLOT(btPowerInvincibilityPressed()));
    connect(btPowerTeleportation, SIGNAL(pressed()), this, SLOT(btPowerTeleportationPressed()));
    connect(btPowerArmore, SIGNAL(pressed()), this, SLOT(btPowerArmorePressed()));

    //POSITIONNEMENT
    btPowerArmore->setX(67);
    btPowerInvincibility->setX(67);
    btPowerTeleportation->setX(67);
    btPowerDestroy->setX(67);

    btPowerArmore->setY(50);
    btPowerInvincibility->setY(110);
    btPowerTeleportation->setY(170);
    btPowerDestroy->setY(230);

    //PARAMETRAGE
    pbMana->insertPlage(0, P_INITIAL_MANA, P_MAX_MANA,Qt::magenta);
    pbMana->setInverse(false);
}
