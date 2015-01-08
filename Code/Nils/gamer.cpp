#include "gamer.h"

/*STATIC*/
QHash<int,Gamer *> lstGamer;

Gamer::Gamer(QColor color, QObject *parent)
    : QObject(parent), color(color)
{
    setNextId();
    lstGamer.insert(getId(), this);
}

Gamer::~Gamer()
{

}

QColor Gamer::getColor() const
{
    return color;
}

Gamer *Gamer::getGamer(int idGamer)
{
    if(lstGamer.contains(idGamer))
    {
        return lstGamer.value(idGamer);
    }
    else
    {
        return 0;
    }
}
