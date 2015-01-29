#include "powerinterface.h"
#include "actionmanager.h"
#include "progressbar.h"
#include "GameComponent/Logic/node.h"
#include "GameComponent/GameInterface/buttonpower.h"
#include "settings.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

PowerInterface::PowerInterface(ActionManager &am, QGraphicsItem * parent) :
    QGraphicsWidget(parent),mana(0),
    am(am)
{
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setUpUI();
    startTimer(clientUpdateLoop());
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

    btPowerArmore->setPowerCDPercent(pcd.percentReload(GA_USEPOWER_ARMORE));
    btPowerInvincibility->setPowerCDPercent(pcd.percentReload(GA_USEPOWER_INVINCIBILITY));
    btPowerTeleportation->setPowerCDPercent(pcd.percentReload(GA_USEPOWER_TELEPORTATION));
    btPowerDestroy->setPowerCDPercent(pcd.percentReload(GA_USEPOWER_DESTROY));

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
    if(this->mana > maxMana())this->mana = maxMana();
}

void PowerInterface::addMana(int mana)
{
    if(mana > 0)this->mana += mana;
    if(this->mana > maxMana())this->mana = maxMana();
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
        btPowerArmorePressed();
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
        btPowerDestroyPressed();
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
        cost = destroyCost();
        countDownTime = destroyCD();
        powerDuration = 0;
        break;
    }
    case GA_USEPOWER_INVINCIBILITY:
    {
        cost = invincibilityCost();
        countDownTime = invincibilityCD();
        powerDuration = invincibilityDuration();
        break;
    }
    case GA_USEPOWER_TELEPORTATION:
    {
        cost = teleportationCost();
        countDownTime = teleportationCD();
        powerDuration = 0;
        break;
    }
    case GA_USEPOWER_ARMORE:
    {
        countDownTime = armorCD();
        powerDuration = armorDuration();
        cost = armorCost();
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
    btPowerArmore = new ButtonPower(ARMOR, this);
    btPowerInvincibility = new ButtonPower(INVINCIBILITY, this);
    btPowerTeleportation = new ButtonPower(TELEPORTATION, this);
    btPowerDestroy = new ButtonPower(DESTRUCTION, this);
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
    pbMana->insertPlage(0, initialMana(), maxMana(),Qt::magenta);
    pbMana->setInverse(false);
}
