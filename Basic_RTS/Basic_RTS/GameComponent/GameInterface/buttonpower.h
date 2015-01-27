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
class ButtonPower : public QGraphicsWidget
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    ButtonPower(BUTTON_TYPE power, QGraphicsItem *parent = 0);

    /*SURCHARGE*/
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    void setPowerCDPercent(double percent);

    /*ASSESSEUR / MUTATEUR*/
    void setSelected(bool b);

    /*SIGNALS/SLOTS*/
signals:
    void pressed();

private:
    /*ENTREE*/
    BUTTON_TYPE power;
    double powerCDPercent;
    bool buttonSelected;
};

#endif // BUTTON_H
