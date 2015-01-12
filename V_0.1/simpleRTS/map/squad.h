#ifndef SQUAD_H
#define SQUAD_H

#include "identitytoken.h"

class Gamer;

/**
 * @brief Représente les ressources envoyées à travers la connexion
 */
class Squad : public IdentityToken
{
public:
    Squad(const Gamer &g);
    virtual ~Squad();
    int getProgress() const;
    void setProgress(int p);
    int getNbRessources() const;
    void setNbRessources(int ressource);
    const Gamer & getOwner() const;

private:
    int progress;
    int nbRessource;
    const Gamer &owner;

};

#endif // SQUAD_H
