#ifndef POWERINTERFACE_H
#define POWERINTERFACE_H

#include <QGraphicsWidget>

class Node;
class Power;
class Button;

namespace GameInterface {
    class PowerInterface;
}

class PowerInterface : public QGraphicsWidget
{
    Q_OBJECT
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    PowerInterface(QGraphicsItem * parent = 0);
    ~PowerInterface();

    /*ASSESSEUR / MUTATEUR*/
    void setMana(int mana);
    void addMana(int mana);
    int getMana()const;

    /*SIGNALS/SLOTS*/
signals:
    void powerDestroyPressed()const;
    void powerInvincibilityPressed()const;
    void powerTeleportationPressed()const;
    void powerArmorePressed()const;
public slots:
    void usePowerDestroy(Node *n);
    void usePowerInvincibility(Node *n);
    void usePowerTeleportation(Node *from, Node *to, int nbUnit);
    void usePowerArmore(Node *n, int nbArmore);
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

    /*TOOL*/
    int mana;
    Power *powerDestroy;
    Power *powerInvincibility;
    Power *powerTeleportation;
    Power *powerArmore;
};

#endif // POWERINTERFACE_H
