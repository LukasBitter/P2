#include "gamer.h"


/*----------------------------------------------------*/
/*STATIC*/
/*----------------------------------------------------*/

QHash<int,Gamer *> lstGamers;
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

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Gamer::Gamer(QColor color, QObject *parent)
    : QObject(parent), color(color), connected(0), ready(0)
{
    setNextId();
    lstGamers.insert(getId(), this);
}

Gamer::~Gamer()
{
    if(name != 0) delete name;
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

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
    name = s;
}
