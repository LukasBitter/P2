#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QMap>
#include "identitytoken.h"

class Gamer;
class Connexion;
class Squad;
class QPainter;
class QObject;

namespace GameComponent {
    class Node;
}

/**
 * @brief Représente les noeuds
 */
class Node : public QGraphicsObject, public IdentityToken
{
    friend class Map;
    Q_OBJECT
public:
    /*STATIC*/
    static Node * getNode(int idNode);

    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit Node(int x, int y, int radius, int ressourcesMax,
                  Gamer *g=0, QGraphicsItem *parent=0);
    virtual ~Node();

    /*SURCHARGE*/
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void advance(int step);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    /*ASSESSEUR / MUTATEUR*/
    int getNbRessources() const;
    void setNbRessources(int r);
    int getRessourcesRate() const;
    void setRessourcesRate(int r);
    int getRessourcesMax() const;
    int getPosY() const;
    int getPosX() const;
    int getRadius() const;
    int getArmorLvl() const;
    void setArmorLvl(int a);
    const Gamer* getOwner();
    void connect(Node &n);
    bool isConnected(Node &n) const;
    Connexion* getConnexion(Node &n) const;

    /*PARSING*/
    QString getUpdateString();
    void updateFromString(QString &s);

    /*EVENEMENT*/
    void incoming(Squad &s);
    void sendSquad(int ressource, Node &n);
private:
    /*INPUT*/
    int nbRessources;
    int armorLvl;
    int ressourcesRate;
    const int ressourcesMax;
    const int posX;
    const int posY;
    const Gamer *owner;
QColor c;

    /*TOOL*/
    int radius;
    QMap<Node *, Connexion *> mapConnexion; //Cle = noeud distant, Valeur = pinteur sur sa connextion
    int counterAdvance;

    /*METHODE PRIVE*/
    void addConnexion(Connexion *c);
    void removeConnexion(Node &n);
    int dealDamageOnArmor(int damage);
};

#endif // NODE_H
