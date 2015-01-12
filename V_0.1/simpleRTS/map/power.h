#ifndef POWER_H
#define POWER_H

class Node;

class Power
{
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    Power();

    /*ASSESSEUR / MUTATEUR*/
    void usePowerDestroy(Node *n);
    void usePowerInvincibility(Node *n);
    void usePowerTeleportation(Node *from, Node *to, int nbUnit);
    void usePowerArmore(Node *n, int nbArmore);
    void setMana(int mana);
    int getMana()const;

private:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    //Ne pas implementer, les copies ne sont pas voulues
    Power(Power &c);
    Power& operator=(const Power&);

    /*TOOL*/
    int mana;
    int cdPowerDestroy;
    int cdPowerInvincibility;
    int cdPowerTeleportation;
    int cdPowerArmore;
};

#endif // POWER_H
