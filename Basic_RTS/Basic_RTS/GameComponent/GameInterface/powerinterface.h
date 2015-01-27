#ifndef POWERINTERFACE_H
#define POWERINTERFACE_H

#include "global.h"
#include "enumlibrary.h"
#include "powercountdown.h"

class Node;
class Button;
class QGraphicsTextItem;
class ActionManager;
class ProgressBar;

namespace GameInterface
{
    class PowerInterface;
}

/**
 * @class PowerInterface
 * @brief Palette pour la gestion des pouvoirs (en jeu)
 *
 * La classe affiche l'interface graphique d'activation des pouvoirs et
 * s'occupe de gestion de temps de recharge
 */
class PowerInterface : public QGraphicsWidget
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    PowerInterface(ActionManager &am, QGraphicsItem *parent = 0);

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
    ProgressBar *pbMana;
    Button *btPowerArmore;
    Button *btPowerInvincibility;
    Button *btPowerTeleportation;
    Button *btPowerDestroy;
    BUTTON_TYPE powerSelected;
    ActionManager &am;

    /*OUTIL*/
    int mana; ///< Réservoir de ressources consomées par les pouvoirs
    PowerCountDown pcd; ///< Gestionnaire des temsp de recharge des pouvoirs

    /*METHODE PRIVE*/
    void setUpUI();
};

#endif // POWERINTERFACE_H
