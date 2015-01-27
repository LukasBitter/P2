#include "buttonressource.h"

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

ButtonRessource::ButtonRessource(BUTTON_TYPE p, QGraphicsItem *parent)
    : QGraphicsWidget(parent), arrow(p), radius(20)
{
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

QRectF ButtonRessource::boundingRect() const
{
    return QRectF(-radius, -radius, 2*radius, 2*radius);
}

QPainterPath ButtonRessource::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void ButtonRessource::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    bool down = option->state & QStyle::State_Sunken;
    bool over= option->state & QStyle::State_MouseOver;

    //DEFINITION DES COULEURS

    QColor normalColor("#53BCE2");
    QColor externColor("#03A2DD");
    QColor downColor = externColor;
    QColor overColor = normalColor.lighter();
    QColor selectedColor = normalColor.lighter();
    QColor textColor(Qt::white);

    //DESSIN DES BOUTONS

    QPen p = painter->pen();
    p.setColor(externColor);
    painter->setPen(p);

    if (down)
    {
        QBrush b = painter->brush();
        b.setColor(downColor);
        b.setStyle(Qt::SolidPattern);
        painter->setBrush(b);
        painter->drawEllipse(boundingRect());
    }
    else if (over)
    {
        QBrush b = painter->brush();
        b.setColor(overColor);
        b.setStyle(Qt::SolidPattern);
        painter->setBrush(b);
        painter->drawEllipse(boundingRect());
    }
    else if (buttonSelected)
    {
        QBrush b = painter->brush();
        b.setColor(selectedColor);
        b.setStyle(Qt::SolidPattern);
        painter->setBrush(b);
        painter->drawEllipse(boundingRect());
    }
    else
    {
        QBrush b = painter->brush();
        b.setColor(normalColor);
        b.setStyle(Qt::SolidPattern);
        painter->setBrush(b);
        painter->drawEllipse(boundingRect());
    }

    //DESSIN DES TEXTES

    p = painter->pen();
    p.setColor(textColor);
    painter->setPen(p);
    QFont f = painter->font();
    f.setPixelSize(radius-7);
    f.setBold(true);
    painter->setFont(f);

    switch (arrow)
    {
    case SET_25:
    {
        painter->drawText(QPoint(-15,5), "25%");
    }
        break;
    case SET_50:
    {
        painter->drawText(QPoint(-15,5), "50%");
    }
        break;
    case SET_75:
    {
        painter->drawText(QPoint(-15,5), "75%");
    }
        break;
    case SET_100:
    {
        painter->drawText(QPoint(-19,5), "100%");
    }
        break;
    default:
        break;
    }
}


void ButtonRessource::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit pressed();
    update();
}

void ButtonRessource::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    update();
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

 void ButtonRessource::setSelected(bool b)
 {
     this->buttonSelected = b;
     update();
 }
