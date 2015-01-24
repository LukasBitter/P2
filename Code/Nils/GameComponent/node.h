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
    explicit Node(int x, int y, int radius, int ressourcesMax,
                  const GamerList &gl, Gamer *g=0);
    explicit Node(QString &create, GamerList &gl);

    /*SURCHARGE*/
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void advance(int step);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    /*ASSESSEUR / MUTATEUR*/
    int getRessources() const;
    int getRessourcesRate() const;
    int getRessourcesMax() const;
    int getArmorLvl() const;
    int getRadius() const;
    bool getInvicibility() const;
    const Gamer* getOwner()const;
    bool isConnected(int nodeId) const;

    void setRessources(int r);
    void setRessourcesRate(int r);
    void setArmorLvl(int a);
    void setInvicibility(bool b);
    void setOwner(const Gamer* g);

    void connect(int nodeId, Connexion *c);
    void disconnect(int nodeId);
    Connexion *getConnexion(int nodeId) const;
    QMap<int, Connexion *> getConnexions() const;

    void incoming(Squad s);
    void sendSquad(int ressource, int nodeId);

    /*MISE A JOUR*/
    QString getUpdateString() const;
    QString getCreationString() const;
    void updateFromString(QString &s);
    QString normalizeSpawn();

private:
    /*ENTREE*/
    int ressourcesMax; ///< Capacité maximale du noeud
    const Gamer *owner; ///< Propriétaire acctuel du noeud
    const GamerList &lstGamer; ///< Liste des joueurs

    /*TOOL*/
    int radius; ///< Rayon du noeud
    int armorLvl; ///< Armure du noeud en nombre de ressources
    int ressourcesRate; ///< Taux de croissance des ressources par "tic"
    int nbRessources; ///< Nombre de ressources acctuellement dans le noeud
    bool invicible; ///< Indique si le noeud est invincible
    int counterAdvance; ///< Reducteur de "tic" pour le gain de ressource
    QMap<int, Connexion *> mapConnexion; ///< Cle = id noeud distant, Valeur = pointeur sur sa connextion

    /*METHODE PRIVE*/
    int dealDamageOnArmor(int damage);
};

#endif // NODE_H
