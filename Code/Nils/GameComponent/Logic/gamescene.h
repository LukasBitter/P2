#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "global.h"

class Node;
class NodeConnectable;
class Connexion;
class GamerList;
class Gamer;

namespace GameComponent
{
    class GameScene;
}

/**
 * @class GameScene
 * @brief Représente une map de jeu logique
 * Si on l'associe avec une editview, il est possible d'éditer et de créer des map et
 * si on l'associe avec une gameview, il est possible de jouer sur la map
 */
class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    GameScene(GamerList &gl, const Gamer *g = 0, QObject *parent=0);
    GameScene(QString create, GamerList &gl, const Gamer *g=0, QObject *parent=0);
    virtual ~GameScene();

    /*SURCHARGE*/
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

    /*ASSESSEUR / MUTATEUR*/
    Node *getNode(int idNode);
    Connexion *getConnexion(int idConnexion);
    const Gamer *isVictory();

    void addNode(Node &n);
    void addConnexion(NodeConnectable &n1, NodeConnectable &n2);
    void removeNode(Node &n);
    void removeConnexion(NodeConnectable &n1, NodeConnectable &n2);

    /*STATISTIQUE*/
    int getTotalRessources(Gamer &g);
    int getAvrageRessourcesRate(Gamer &g);
    int getTotalRessources();
    int getAvrageRessourcesRate();

    /*MISE A JOUR*/
    QString getUpdateString();
    void updateFromString(QString s);
    QString getCreationString();
    QStringList normalizeSpawn();
    static bool isContainsPrivateChar(QString &s);

private:
    /*ENTREE*/
    const Gamer *owner; ///< Joueur au commande de la map
    GamerList &lstGamer; ///< Liste des joueurs présents

    /*OUTIL*/
    QHash<int, Node *> lstNode; ///< Liste de tous les noeuds
    QHash<int, Connexion *> lstConnexion; ///< Liste de toutes les connexions
};

#endif // GAMESCENE_H
