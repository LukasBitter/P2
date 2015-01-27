#ifndef RESSOURCESINTERFACE_H
#define RESSOURCESINTERFACE_H

#include "global.h"

class Button;
class QGraphicsTextItem;
class ActionManager;

namespace GameInterface
{
    class RessourcesInterface;
}

/**
 * @class RessourcesInterface
 * @brief Palette pour la gestion du pourcentage d'unitéa envoyer
 */
class RessourcesInterface : public QGraphicsWidget
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    RessourcesInterface(ActionManager &am, QGraphicsItem *parent = 0);

    /*SURCHARGE*/
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /*ASSESSEUR / MUTATEUR*/
    double getPercentToSend()const;
    void setPercentToSend(double p);

    /*SIGNALS/SLOTS*/
public slots:
    void shortCutPressed(QKeyEvent *e);
private slots:
    void btIncrasePressed();
    void btDicrasePressed();

private:
    /*INTERFACE*/
    Button *btIncrase;
    Button *btDicrase;
    QGraphicsTextItem *txtPercent;
    ActionManager &am;

    /*OUTIL*/
    double percentToSend; ///< Pourcentage du noeud à envoyer lors d'un envoi

    /*METHODE PRIVE*/
    void setUpUI();
};

#endif // RESSOURCESINTERFACE_H
