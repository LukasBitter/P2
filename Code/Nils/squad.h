#ifndef SQUAD_H
#define SQUAD_H

class Gamer;

/**
 * @brief Représente les ressources envoyées à travers la connexion
 */
class Squad
{
public:
    Squad(const Gamer &g);
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
