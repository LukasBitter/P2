#ifndef NODECOMBAT_H
#define NODECOMBAT_H

#include <QGraphicsItem>
#include <QMap>
#include "node.h"

class Gamer;
class Connexion;
class Squad;
class QPainter;
class GamerList;

namespace GameComponent
{
class NodeCombat;
}

/**
 * @class NodeCombat
 * @brief Représente les noeuds prenable par les joueur
 */
class NodeCombat : public Node
{

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit NodeCombat(int x, int y, int radius, int ressourcesMax,
                  const GamerList &gl, Gamer *g=0);
    explicit NodeCombat(QString &create, GamerList &gl);

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

    void setRessources(int r);
    void setRessourcesRate(int r);
    void setArmorLvl(int a);
    void setInvicibility(bool b);
    void setOwner(const Gamer* g);

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
    int ressourcesMax; ///< Capacité maximale du noeud
    const Gamer *owner; ///< Propriétaire acctuel du noeud
    const GamerList &lstGamer; ///< Liste des joueurs

    /*TOOL*/
    int armorLvl; ///< Armure du noeud en nombre de ressources
    int ressourcesRate; ///< Taux de croissance des ressources par "tic"
    int nbRessources; ///< Nombre de ressources acctuellement dans le noeud
    bool invicible; ///< Indique si le noeud est invincible
    int counterAdvance; ///< Reducteur de "tic" pour le gain de ressource

    /*METHODE PRIVE*/
    int dealDamageOnArmor(int damage);
};

#endif // NODECOMBAT_H
