#include "gamer.h"
#include "gamerlist.h"
#include <QDebug>


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

/**
 * @brief Gamer::Gamer création d'un nouveau gamer
 * @param parent QObject parent
 *
 * A la création un identifiant unique est défini.
 */
Gamer::Gamer(QObject *parent)
    : QObject(parent), ready(false), name(""), color(Qt::white)
{
    setNextId();
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

void Gamer::setColor(QColor c)
{
    color.setRed(c.red());
    color.setGreen(c.green());
    color.setBlue(c.blue());
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
    return isReady();
}

QString Gamer::getName() const
{
    return name;
}

void Gamer::setReady(bool b)
{
    ready = b;
}

void Gamer::setName(QString s)
{
    name = s;
}

/*----------------------------------------------------*/
/*MISE A JOUR*/
/*----------------------------------------------------*/

QString Gamer::getUpdateString()
{
    return QString("%1,%2,%3,%4,%5").arg(color.red()).
           arg(color.green()).arg(color.blue()).arg(name).arg(ready);
}

void Gamer::updateFromString(QString &s)
{
    QStringList nodeStr = s.split(",");
    if(nodeStr.size() == 5)
    {
        color.setRed(nodeStr.first().toInt());
        nodeStr.pop_front();
        color.setGreen(nodeStr.first().toInt());
        nodeStr.pop_front();
        color.setBlue(nodeStr.first().toInt());
        nodeStr.pop_front();
        name = nodeStr.first();
        nodeStr.pop_front();
        ready = (nodeStr.first() == "1" ? true : false);
    }
    else
    {
        qCritical()<<"Gamer : unexpected case in 'updateFromString'";
    }
}
