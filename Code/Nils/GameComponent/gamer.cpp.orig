#include "gamer.h"

#include <qdebug.h>


/*----------------------------------------------------*/
/*METHODE DE CLASSE*/
/*----------------------------------------------------*/

QHash<int,Gamer *> lstGamers;

const QHash<int, Gamer *> &Gamer::getLstGamer()
{
    return lstGamers;
}

Gamer *Gamer::getGamer(int idGamer)
{
    if(lstGamers.contains(idGamer))
    {
        return lstGamers.value(idGamer);
    }
    else
    {
        return 0;
    }
}

QString Gamer::getLstGamerUpdateString()
{
    QString s;
    foreach (Gamer *g, lstGamers)
    {
        s.append(QString("%1.%2/").arg(g->getId()).arg(g->getUpdateString()));
    }
    return s;
}

void Gamer::updateLstGamerFromString(QString &s)
{
    QStringList allGamers = s.split("/");

    foreach (QString s, allGamers)
    {
        QStringList gamerStr = s.split(".");
        if(gamerStr.size() == 2)
        {
            int numberId = gamerStr.first().toInt();
            gamerStr.pop_front();
            QString &data = gamerStr.first();

            Gamer *g = Gamer::getGamer(numberId);
            if(g == 0)
            {
                g = new Gamer();
                g->setId(numberId);
            }
            g->updateFromString(data);
        }
    }
}

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Gamer::Gamer(QObject *parent)
    : QObject(parent), connected(0), ready(0)
{
    setNextId();
    lstGamers.insert(getId(), this);
    //name = new QString("");
}

Gamer::~Gamer()
{
    if(name != 0) delete name;
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

bool Gamer::isConnected() const
{
    return isConnected();
}

bool Gamer::isReady() const
{
    return isReady();
}

QString *Gamer::getName() const
{
    return name;
}

void Gamer::setConnected(bool b)
{
    connected =b;
}

void Gamer::setReady(bool b)
{
    ready = b;
}

void Gamer::setName(QString *s)
{
    if(s == 0)
    {
        name = new QString("");
    }
    else
    {
        name = s;
    }
}

/*----------------------------------------------------*/
/*MISE A JOUR*/
/*----------------------------------------------------*/

QString Gamer::getUpdateString()
{
    return QString("%1,%2,%3,%4,%5,%6").arg(color.red()).
            arg(color.green()).arg(color.blue()).arg(*name).
            arg(connected).arg(ready);
}

void Gamer::updateFromString(QString &s)
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
        delete name;
        name = new QString(nodeStr.first());
        nodeStr.pop_front();
        connected = (nodeStr.first() == "1" ? true : false);
        nodeStr.pop_front();
        ready = (nodeStr.first() == "1" ? true : false);
    }
}
