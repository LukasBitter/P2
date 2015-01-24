#ifndef POWER_H
#define POWER_H

class Node;

namespace GameInterface
{
    class Power;
}

/**
 * @class Power
 * @brief Classe parent de tous les pouvoirs
 */
class Power
{
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    Power(int countDownTime, int powerTime);

    /*SURCHARGE*/
    void enablePower();
    void enablePower(Node *n);
    void enablePower(Node *n1, Node *n2);
    void enablePower(int v, Node *n);
    void enablePower(int v, Node *n1, Node *n2);

    virtual void powerAction();
    virtual void powerAction(Node *n);
    virtual void powerAction(Node *n1, Node *n2);
    virtual void powerAction(int v, Node *n);
    virtual void powerAction(int v, Node *n1, Node *n2);

    virtual void onPowerFinishing();
    virtual void onPowerReady();

    /*ASSESSEUR / MUTATEUR*/
    bool isReady()const;
    int getCountDownTime() const;
    int getPowerTime() const;
    int getReloadCD() const;
    int getPowerCD() const;
    float percentReload() const;
    void advence();

private:
    int countDownTime;
    int powerTime;
    /*OUTIL*/
    int reloadCD; ///< Temps de recharge du pouvoir
    int powerCD; ///< Durée du pouvoir

    /*METHODE PRIVE*/
    void activateCountDown();
};

#endif // POWER_H
