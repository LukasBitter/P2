#include "squad.h"

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Squad::Squad(const Gamer &g) : owner(g), progress(0), nbRessource(0)
{

}

Squad::Squad(const Squad &s) : owner(s.owner)
{
    progress = s.progress;
    nbRessource = s.nbRessource;
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
