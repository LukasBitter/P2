#ifndef NODE_H
#define NODE_H

#include "identitytoken.h"
#include "global.h"

class Gamer;
class Connexion;
class Squad;
class GamerList;

namespace GameComponent
{
    class Node;
}

/**
 * @class Node
 * @brief Représente les noeuds de manière générale
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
    virtual QColor getColor();
    virtual void setColor(QColor c);
    virtual int getRadius() const;
    virtual const Gamer* getOwner()const = 0;
    virtual void setOwner(const Gamer* g) = 0;

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
    QColor color;
    QMap<int, Connexion *> mapConnexion; ///< Liste des connexion du noeud (Cle = id noeud distant, Valeur = pointeur sur sa connextion)
};

#endif // NODE_H
