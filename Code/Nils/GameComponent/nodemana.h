#ifndef NODEMANA_H
#define NODEMANA_H

#include <QGraphicsItem>
#include <QMap>
#include <QObject>
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
 * @brief Représente les noeuds augmantant le mana du joueur
 */
class NodeMana :  public QObject, public Node
{
    Q_OBJECT

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

    /*SIGNALS/SLOTS*/
signals:
    void manaEmission(int gamerId, int mana);
private:
    /*ENTREE*/
    const GamerList &lstGamer; ///< Liste des joueurs
};

#endif // NODEMANA_H
