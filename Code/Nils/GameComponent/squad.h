#ifndef SQUAD_H
#define SQUAD_H

class Gamer;

namespace GameComponent
{
    class Squad;
}

/**
 * @class Squad
 * @brief Représente les ressources envoyées à travers la connexion
 *
 * Ce n'est pas un objet QGraphicsItem utilisé dans la scène,
 * mais une structure logique utilisé par la classe Connexion.
 */
class Squad
{
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    Squad(const Gamer &g);
    Squad(const Squad &s);

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
