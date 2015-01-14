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
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    Squad(const Gamer &g);
    virtual ~Squad();

    /*ASSESSEUR / MUTATEUR*/
    int getProgress() const;
    void setProgress(int p);
    int getNbRessources() const;
    void setNbRessources(int ressource);
    const Gamer & getOwner() const;

private:
    /*ENTREE*/
    const Gamer &owner;

    /*OUTIL*/
    int progress;
    int nbRessource;
};

#endif // SQUAD_H
