#include "buttonpower.h"

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

ButtonPower::ButtonPower(BUTTON_TYPE p, QGraphicsItem *parent)
    : QGraphicsWidget(parent), power(p), buttonSelected(false),
      powerCDPercent(0)
{
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

QRectF ButtonPower::boundingRect() const
{
    return QRectF(-50, -50, 100, 100);
}

QPainterPath ButtonPower::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void ButtonPower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
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
    default:
        break;
    }

    if (down)
    {
        buttonPath += "Click.png";
        this->buttonSelected = true;
    }
    else if (over)
    {
        buttonPath += "Hover.png";
    }
    else if (this->buttonSelected)
    {
        buttonPath += "Click.png";
    }
    else
    {
        buttonPath += "Normal.png";
    }

    const QPixmap buttonImg = QPixmap(buttonPath);

    QRectF r = boundingRect();
    painter->drawPixmap(r, buttonImg,source);


    QPen p = painter->pen();
    p.setWidth(2);
    p.setColor(Qt::green);

    painter->setPen(p);
    painter->rotate(-90);

    painter->save();
    for(int i=0;i<=((this->powerCDPercent/100)*60);++i)
    {
        painter->drawLine(25, 0, 28, 0);
        painter->rotate(6.0);
    }
    painter->restore();
}


void ButtonPower::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit pressed();
    update();
}

void ButtonPower::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    update();
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

 void ButtonPower::setPowerCDPercent(double percent)
 {
     this->powerCDPercent = percent;
     this->update();
 }

 void ButtonPower::setSelected(bool b)
 {
     this->buttonSelected = b;
 }
