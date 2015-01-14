#ifndef POWER_H
#define POWER_H

#include <QObject>

class QTimer;
class Node;

namespace GameInterface {
    class Power;
}

/**
 * @class Power
 * @brief Classe parent de tous les pouvoirs
 */
class Power : public QObject
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    Power(int countDown, int powerTime, QObject *parent=0);

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

    /*SIGNALS/SLOTS*/
private slots:
    void restorCountDown();
    void powerEnd();

private:
    /*OUTIL*/
    QTimer *countDown;
    QTimer *endPower;
    bool ready;

    /*METHODE PRIVE*/
    void activateCountDown();
};

#endif // POWER_H
