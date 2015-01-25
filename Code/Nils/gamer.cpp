#include "gamer.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

/**
 * @brief Gamer::Gamer création d'un nouveau gamer
 * @param parent QObject parent
 *
 * A la création un identifiant unique est défini.
 */
Gamer::Gamer(QObject *parent):
    QObject(parent),
    ready(false),
    name(""),
    color(Qt::white),
    slotNumber(-1),
    socket(0)
{
    setNextId();
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

void Gamer::setColor(const QColor &c)
{
    color = c;
}

QColor Gamer::getColor() const
{
    return color;
}

void Gamer::setSocket(QTcpSocket *s)
{
    socket = s;
}

QTcpSocket *Gamer::getSocket() const
{
    return socket;
}

bool Gamer::isReady() const
{
    return ready;
}

QString Gamer::getName() const
{
    return name;
}

void Gamer::setReady(bool b)
{
    ready = b;
}

void Gamer::setName(const QString &s)
{
    name = s;
}

void Gamer::setSlotNumber(int no)
{
    slotNumber = no;
}

int Gamer::getSlotNumber()const
{
    return slotNumber;
}

/*----------------------------------------------------*/
/*MISE A JOUR*/
/*----------------------------------------------------*/

QString Gamer::getUpdateString() const
{
    return QString("%1,%2,%3,%4,%5,%6").arg(color.red()).
           arg(color.green()).arg(color.blue()).arg(name).
           arg(ready).arg(slotNumber);
}

void Gamer::updateFromString(const QString &s)
{
    QStringList nodeStr = s.split(",");

    if(nodeStr.size() == 6)
    {
        color.setRed(nodeStr.first().toInt());
        nodeStr.pop_front();
        color.setGreen(nodeStr.first().toInt());
        nodeStr.pop_front();
        color.setBlue(nodeStr.first().toInt());
        nodeStr.pop_front();
        name = nodeStr.first();
        nodeStr.pop_front();
        ready = nodeStr.first().toInt();
        nodeStr.pop_front();
        slotNumber = nodeStr.first().toInt();
    }
    else
    {
        qCritical()<<"Gamer : unexpected case in 'updateFromString'";
    }
}
