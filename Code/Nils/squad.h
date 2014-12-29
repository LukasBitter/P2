#ifndef SQUAD_H
#define SQUAD_H

#include <QMutex>

class Gamer;

/**
 * @brief Représente les ressources envoyées à travers la connexion
 *
 * Classe thread-safe
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
    mutable QMutex mutex;   //Verroux sur l'objet

};

#endif // SQUAD_H
