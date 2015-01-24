#ifndef POWERINTERFACE_H
#define POWERINTERFACE_H

#include "global.h"
#include "enumlibrary.h"
#include "GameComponent/GameInterface/Powers/powercountdown.h"

class Node;
class Button;
class QGraphicsTextItem;

namespace GameInterface
{
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

    /*SURCHARGE*/
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); 
    void timerEvent(QTimerEvent *event);

    /*ASSESSEUR / MUTATEUR*/
    void setMana(int mana);
    void addMana(int mana);
    int getMana()const;
    const PowerCountDown &getCountDownManager()const;

    /*SIGNALS/SLOTS*/
signals:
    void powerPressed(ACTIONS a);
public slots:
    void shortCutPressed(QKeyEvent *e);
    void usePower(ACTIONS a, Node* n1, Node* n2);
private slots:
    void btPowerDestroyPressed();
    void btPowerInvincibilityPressed();
    void btPowerTeleportationPressed();
    void btPowerArmorePressed();


private:
    /*INTERFACE*/
    QGraphicsTextItem *txtMana;
    Button *btPowerDestroy;
    Button *btPowerInvincibility;
    Button *btPowerTeleportation;
    Button *btPowerArmore;
    QGraphicsTextItem *txtCdPowerDestroy;
    QGraphicsTextItem *txtCdPowerInvincibility;
    QGraphicsTextItem *txtCdPowerTeleportation;
    QGraphicsTextItem *txtCdPowerArmore;

    /*OUTIL*/
    int mana; ///< Réservoir de ressources consomées par les pouvoirs
    PowerCountDown pcd;

    /*METHODE PRIVE*/
    void setUpUI();
    void updateCD();
};

#endif // POWERINTERFACE_H
