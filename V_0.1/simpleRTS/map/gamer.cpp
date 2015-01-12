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
    : QObject(parent), color(color)
{
    setNextId();
    lstGamers.insert(getId(), this);
}

Gamer::~Gamer()
{

}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

QColor Gamer::getColor() const
{
    return color;
}
