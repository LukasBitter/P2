#ifndef POWERINTERFACE_H
#define POWERINTERFACE_H

#include <QGraphicsWidget>
#include "ennum.h"

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
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

    /*ASSESSEUR / MUTATEUR*/
    void setMana(int mana);
    void addMana(int mana);
    int getMana()const;

    /*SIGNALS/SLOTS*/
signals:
    void powerPressed(PowerName name)const;
public slots:
    void usePowerDestroy(Node *n);
    void usePowerInvincibility(Node *n);
    void usePowerTeleportation(Node *from, Node *to);
    void usePowerArmore(Node *n);
private slots:
    void btPowerDestroyPressed()const;
    void btPowerInvincibilityPressed()const;
    void btPowerTeleportationPressed()const;
    void btPowerArmorePressed()const;

private:
    /*INTERFACE*/
    Button *btPowerDestroy;
    Button *btPowerInvincibility;
    Button *btPowerTeleportation;
    Button *btPowerArmore;

    /*OUTIL*/
    int mana;
    Power *powerDestroy;
    Power *powerInvincibility;
    Power *powerTeleportation;
    Power *powerArmore;
};

#endif // POWERINTERFACE_H
