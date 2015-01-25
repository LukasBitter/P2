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
 * @brief Scene de jeu
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
    const Gamer *owner; ///< Joueur actuellement au commande de la map
    GamerList &lstGamer; ///< Liste des joueurs

    /*OUTIL*/
    QHash<int, Node *> lstNode; ///< Liste de tous les noeuds
    QHash<int, Connexion *> lstConnexion; ///< Liste de toutes les connexions
};

#endif // GAMESCENE_H
