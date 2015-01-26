#include "button.h"

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Button::Button(POWER p, QGraphicsItem *parent)
    : QGraphicsWidget(parent), power(p)
{
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

QRectF Button::boundingRect() const
{
    return QRectF(-50, -50, 100, 100);
}

QPainterPath Button::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    bool down = option->state & QStyle::State_Sunken;
    bool over= option->state & QStyle::State_MouseOver;

    QString buttonPath;
    QRectF source(0.0, 0.0, 432.0, 432.0);

    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::Antialiasing, true);

    switch (this->power)
    {
    case ARMOR: buttonPath = ":/Button1";
        break;
    case INVINCIBILITY: buttonPath = ":/Button2";
        break;
    case TELEPORTATION: buttonPath = ":/Button3";
        break;
    case DESTRUCTION: buttonPath = ":/Button4";
        break;
    }

    if (down)
    {
        buttonPath += "Click.png";
    }
    else if (over)
    {
        buttonPath += "Hover.png";
    }
    else
    {
        buttonPath += "Normal.png";
    }

    const QPixmap buttonImg = QPixmap(buttonPath);

    QRectF r = boundingRect();
    painter->drawPixmap(r, buttonImg,source);


    for(int i=0;i<=((this->powerPercent/100)*60);i++)
    {
        painter->drawLine(92, 0, 96, 0);
        painter->rotate(6.0);
    }

//    QRectF r = boundingRect();
//    QLinearGradient grad(r.topLeft(), r.bottomRight());
//    grad.setColorAt(down ? 1 : 0, option->state & QStyle::State_MouseOver ? Qt::white : Qt::lightGray);
//    grad.setColorAt(down ? 0 : 1, Qt::darkGray);
//    painter->setPen(Qt::darkGray);
//    painter->setBrush(grad);
//    painter->drawEllipse(r);
//    QLinearGradient grad2(r.topLeft(), r.bottomRight());
//    grad.setColorAt(down ? 1 : 0, Qt::darkGray);
//    grad.setColorAt(down ? 0 : 1, Qt::lightGray);
//    painter->setPen(Qt::NoPen);
//    painter->setBrush(grad);
//    if (down)painter->translate(2, 2);
//    painter->drawEllipse(r.adjusted(5, 5, -5, -5));
//    if (down)painter->translate(-2, -2);

//    painter->setPen( Qt::SolidLine);
//    painter->drawText(QPoint(0, 0),text);
}


void Button::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit pressed();
    update();
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    update();
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

 void Button::setPowerPercent(double percent)
 {
     this->powerPercent = percent;
 }
