#ifndef NODECONNECTABLE_H
#define NODECONNECTABLE_H

#include "node.h"

class Gamer;
class Connexion;
class Squad;
class QPainter;

namespace GameComponent
{
    class NodeConnectable;
}

/**
 * @class NodeConnectable
 * @brief Représente les noeuds de manière générale
 */
class NodeConnectable : public Node
{

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit NodeConnectable(int x, int y, int radius);

    /*ASSESSEUR / MUTATEUR*/
    virtual bool isConnected(int nodeId) const;
    virtual void connect(int nodeId, Connexion *c);
    virtual void disconnect(int nodeId);
    virtual Connexion *getConnexion(int nodeId) const;
    virtual QMap<int, Connexion *> getConnexions() const;

protected:
    /*TOOL*/
    QMap<int, Connexion *> mapConnexion; ///< Liste des connexion du noeud (Cle = id noeud distant, Valeur = pointeur sur sa connextion)
};

#endif // NODECONNECTABLE_H
