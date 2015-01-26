#ifndef NODEMANA_H
#define NODEMANA_H

#include "global.h"
#include "node.h"

class Gamer;
class Connexion;
class Squad;
class QPainter;
class GamerList;

namespace GameComponent
{
    class NodeMana;
}

/**
 * @class NodeMana
 * @brief Représente les noeuds de restauration du mana
 * Les joueurs peuvent envoyer des ressources vers ces noeud afin de remonter leur mana.
 * Les ressources sont imédiattement convertie, il est impossible de prendre ce noeud
 * ou de passer au travers.
 */
class NodeMana : public Node
{

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit NodeMana(int x, int y, int radius, const GamerList &gl);
    explicit NodeMana(QString &create, GamerList &gl);

    /*ASSESSEUR / MUTATEUR*/
    const Gamer* getOwner()const;
    void setOwner(const Gamer *g);

    void incoming(Squad s);
    void sendSquad(int ressource, int nodeId);

    /*MISE A JOUR*/
    QString getUpdateString() const;
    QString getCreationString() const;
    void updateFromString(QString &s);
    QString normalizeSpawn();
    static bool isContainsPrivateChar(QString &s);

private:
    /*ENTREE*/
    const GamerList &lstGamer; ///< Liste des joueurs présents
};

#endif // NODEMANA_H
