#ifndef POWERINTERFACE_H
#define POWERINTERFACE_H

#include "global.h"
#include "enumlibrary.h"
#include "GameComponent/GameInterface/Powers/powerarmore.h"
#include "GameComponent/GameInterface/Powers/powerdestroy.h"
#include "GameComponent/GameInterface/Powers/powerinvincibility.h"
#include "GameComponent/GameInterface/Powers/powerteleportation.h"

class Node;
class Power;
class Button;

namespace GameInterface {
class PowerInterface;
}

/**
 * @class PowerInterface
 * @brief Interface utilisateur
 *
 * Regroupe les boutons d'activation des pouvoir et gère le mana du joueur
 */
class PowerInterface : public QGraphicsWidget
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    PowerInterface(QGraphicsItem * parent = 0);
    ~PowerInterface();

    /*SURCHARGE*/
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); 

    /*ASSESSEUR / MUTATEUR*/
    void setMana(int mana);
    void addMana(int mana);
    int getMana()const;

    /*SIGNALS/SLOTS*/
signals:
    void powerPressed(POWER_NAME name);
public slots:
    void usePowerDestroy(Node *n);
    void usePowerInvincibility(Node *n);
    void usePowerTeleportation(Node *from, Node *to);
    void usePowerArmore(Node *n);

    void shortCutPressed(QKeyEvent *e);
    void usePower(POWER_NAME name, Node *n1, Node *n2);
private slots:
    void btPowerDestroyPressed();
    void btPowerInvincibilityPressed();
    void btPowerTeleportationPressed();
    void btPowerArmorePressed();

private:
    /*INTERFACE*/
    Button *btPowerDestroy;
    Button *btPowerInvincibility;
    Button *btPowerTeleportation;
    Button *btPowerArmore;

    /*OUTIL*/
    int mana; ///< Réservoir de ressources consomées par les pouvoirs
    PowerDestroy powerDestroy;
    PowerInvincibility powerInvincibility;
    PowerTeleportation powerTeleportation;
    PowerArmore powerArmore;

    /*METHODE PRIVE*/
    void setUpUI();
};

#endif // POWERINTERFACE_H
