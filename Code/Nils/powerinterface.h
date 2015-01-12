#ifndef POWER_H
#define POWER_H

#include <QWidget>
class QPushButton;
class Node;

class PowerInterface : public QWidget
{
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    PowerInterface(QWidget * parent = 0);
    ~PowerInterface();

    /*ASSESSEUR / MUTATEUR*/
    void setMana(int mana);
    void addMana(int mana);
    int getMana()const;
signals:
    void btPowerDestroyPressed()const;
    void btPowerInvincibilityPressed()const;
    void btPowerTeleportationPressed()const;
    void btPowerArmorePressed()const;
public slots:
    void usePowerDestroy(Node *n);
    void usePowerInvincibility(Node *n);
    void usePowerTeleportation(Node *from, Node *to, int nbUnit);
    void usePowerArmore(Node *n, int nbArmore);

private:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    //Ne pas implementer, les copies ne sont pas voulues
    PowerInterface(PowerInterface &c);
    PowerInterface& operator=(const PowerInterface&);

    /*INTERFACE*/
    QPushButton *btPowerDestroy;
    QPushButton *btPowerInvincibility;
    QPushButton *btPowerTeleportation;
    QPushButton *btPowerArmore;

    /*TOOL*/
    int mana;
    int cdPowerDestroy;
    int cdPowerInvincibility;
    int cdPowerTeleportation;
    int cdPowerArmore;
};

#endif // POWER_H
