#include "squad.h"

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Squad::Squad(const Gamer &g) : owner(g)
{
    setNextId();
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

int Squad::getProgress() const
{
    return progress;
}

void Squad::setProgress(int p)
{
    progress = p;
}

int Squad::getNbRessources() const
{
    return nbRessource;
}

void Squad::setNbRessources(int ressource)
{
    nbRessource = ressource;
}

const Gamer & Squad::getOwner() const
{
    return owner;
}
