#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsWidget>

namespace GameInterface {
    class Button;
}

class Button : public QGraphicsWidget
{
    Q_OBJECT
public:
    Button(const QString &s, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
signals:
    void pressed();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

private:
    QString text;
};

#endif // BUTTON_H
