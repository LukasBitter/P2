#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsWidget>

namespace GameInterface {
class Button;
}

/**
 * @class Button
 * @brief Bouton poussoir utilisable avec le GraphicsViewFramwork
 */
class Button : public QGraphicsWidget
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    Button(const QString &s, QGraphicsItem *parent = 0);

    /*SURCHARGE*/
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

    /*SIGNALS/SLOTS*/
signals:
    void pressed();

private:
    /*ENTREE*/
    QString text; ///< Texte du bouton
};

#endif // BUTTON_H
