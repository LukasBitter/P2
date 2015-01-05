#include "squad.h"


Squad::Squad(const Gamer &g) : owner(g)
{
}

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
    //Set de type simple, pas besoin de vérouiller
    nbRessource = ressource;
}

const Gamer & Squad::getOwner() const
{
    return owner;
}
