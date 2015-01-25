#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>

class Node;
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
    void addConnexion(Node &n1, Node &n2);
    void removeNode(Node &n);
    void removeConnexion(Node &n1, Node &n2);

    /*MISE A JOUR*/
    QString getUpdateString();
    void updateFromString(QString s);
    QString getCreationString();
    QStringList normalizeSpawn();
    static bool isContainsPrivateChar(QString &s);

    /*SIGNALS/SLOTS*/
signals:
    void manaEmission(int gamerId, int mana);
private slots:
    void onManaEmission(int gamerId, int mana);

private:
    /*ENTREE*/
    const Gamer *owner; ///< Joueur au commande de la map
    GamerList &lstGamer; ///< Liste des joueurs présents

    /*OUTIL*/
    QHash<int, Node *> lstNode; ///< Liste de tous les noeuds
    QHash<int, Connexion *> lstConnexion; ///< Liste de toutes les connexions
};

#endif // GAMESCENE_H
