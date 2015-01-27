#ifndef BUTTONRESSOURCE_H
#define BUTTONRESSOURCE_H

#include "global.h"
#include "enumlibrary.h"

namespace GameInterface
{
    class Button;
}

/**
 * @class ButtonRessource
 * @brief Bouton poussoir pour interface avec le GraphicsViewFramwork
 */
class ButtonRessource : public QGraphicsWidget
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    ButtonRessource(BUTTON_TYPE arrow, QGraphicsItem *parent = 0);

    /*SURCHARGE*/
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    void setPowerPercent(double percent);

    /*ASSESSEUR / MUTATEUR*/
    void setSelected(bool b);

    /*SIGNALS/SLOTS*/
signals:
    void pressed();

private:
    /*ENTREE*/
    BUTTON_TYPE arrow;
    bool buttonSelected;
    const int radius;

    void drawImage();
};

#endif // BUTTONRESSOURCE_H
