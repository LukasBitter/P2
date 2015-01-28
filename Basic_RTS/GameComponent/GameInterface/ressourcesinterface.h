#ifndef RESSOURCESINTERFACE_H
#define RESSOURCESINTERFACE_H

#include "global.h"

class ButtonRessource;
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
    void bt25Pressed();
    void bt50Pressed();
    void bt75Pressed();
    void bt100Pressed();

private:
    /*INTERFACE*/
    ButtonRessource *bt25Percent;
    ButtonRessource *bt50Percent;
    ButtonRessource *bt75Percent;
    ButtonRessource *bt100Percent;
    ActionManager &am;

    /*OUTIL*/
    double percentToSend; ///< Pourcentage du noeud à envoyer lors d'un envoi

    /*METHODE PRIVE*/
    void setUpUI();
    void resetSelection();
};

#endif // RESSOURCESINTERFACE_H
