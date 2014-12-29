#include "updatable.h"

namespace
{
    unsigned int currentID = 0;
}

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Updatable::Updatable(QObject *parent)
    : QObject(parent)
{
    mutex.lock();
    id = currentID++;
    mutex.unlock();
}

Updatable::~Updatable()
{

}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

unsigned int Updatable::getId() const
{
    return id;
}
