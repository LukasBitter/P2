#ifndef BUTTON_H
#define BUTTON_H

#include "global.h"
#include "enumlibrary.h"

namespace GameInterface
{
    class Button;
}

/**
 * @class Button
 * @brief Bouton poussoir pour interface avec le GraphicsViewFramwork
 */
class Button : public QGraphicsWidget
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    Button(POWER power, QGraphicsItem *parent = 0);

    /*SURCHARGE*/
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    void setPowerPercent(double percent);

    /*SIGNALS/SLOTS*/
signals:
    void pressed();

private:
    /*ENTREE*/
    POWER power;
    double powerPercent;
};

#endif // BUTTON_H
