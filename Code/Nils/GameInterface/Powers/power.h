#ifndef POWER_H
#define POWER_H

#include <QObject>

class QTimer;
class Node;

namespace GameInterface {
    class Power;
}

class Power : public QObject
{
    Q_OBJECT
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    Power(int countDown, QObject *parent=0);
    ~Power();

    /*SURCHARGE*/
    virtual void enablePower();
    virtual void enablePower(Node *n);
    virtual void enablePower(Node *n1, Node *n2);
    virtual void enablePower(int v, Node *n);
    virtual void enablePower(int v, Node *n1, Node *n2);
    virtual void onPowerFinishing();

    /*ASSESSEUR / MUTATEUR*/
    bool isReady()const;

private slots:
    void restorCountDown();
private:
    QTimer *timer;
    bool ready;
    void activateCountDown();
};

#endif // POWER_H
