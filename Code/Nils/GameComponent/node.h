#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QMap>
#include "identitytoken.h"

class Gamer;
class Connexion;
class Squad;
class QPainter;
class GamerList;

namespace GameComponent
{
class Node;
}

/**
 * @class Node
 * @brief Représente les noeuds
 */
class Node : public QGraphicsItem, public IdentityToken
{

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit Node(int x, int y, int radius);

    /*FABRIQUE*/
    static Node* createNode(QString &create, GamerList &gl);

    /*SURCHARGE*/
    QRectF boundingRect() const;
    virtual void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    /*ASSESSEUR / MUTATEUR*/
    virtual int getRadius() const;
    virtual const Gamer* getOwner()const = 0;
    virtual void setOwner(const Gamer* g) = 0;
    virtual bool isConnected(int nodeId) const;

    virtual void connect(int nodeId, Connexion *c);
    virtual void disconnect(int nodeId);
    virtual Connexion *getConnexion(int nodeId) const;
    virtual QMap<int, Connexion *> getConnexions() const;

    virtual void incoming(Squad s) = 0;
    virtual void sendSquad(int ressource, int nodeId) = 0;

    /*MISE A JOUR*/
    virtual QString getUpdateString() const = 0;
    virtual QString getCreationString() const = 0;
    virtual void updateFromString(QString &s) = 0;
    virtual QString normalizeSpawn() = 0;
protected:
    /*TOOL*/
    int radius; ///< Rayon du noeud
    QMap<int, Connexion *> mapConnexion; ///< Cle = id noeud distant, Valeur = pointeur sur sa connextion
};

#endif // NODE_H
