#ifndef SQUAD_H
#define SQUAD_H

#include "identitytoken.h"

class Gamer;

/**
 * @class Squad
 * @brief Représente les ressources envoyées à travers la connexion
 *
 * N'est pas un objet QGraphicsItem utilisé dans la scène, mais une structure
 * logique utilisé par la classe Connexion
 */
class Squad : public IdentityToken
{
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    Squad(const Gamer &g);

    /*ASSESSEUR / MUTATEUR*/
    int getProgress() const;
    void setProgress(int p);
    int getNbRessources() const;
    void setNbRessources(int ressource);
    const Gamer & getOwner() const;

private:
    /*ENTREE*/
    const Gamer &owner; ///< Propriétaire de l'equipe

    /*OUTIL*/
    int progress; ///< Progression actuelle
    int nbRessource; ///< Nombre de ressource contenue
};

#endif // SQUAD_H
