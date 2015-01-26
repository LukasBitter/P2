#ifndef CONNEXION_H
#define CONNEXION_H

#include "identitytoken.h"
#include "global.h"

class NodeConnectable;
class QPainter;
class Gamer;
class QObject;
class Squad;
class GamerList;

namespace GameComponent
{
    class Connexion;
}

/**
 * @class Connexion
 * @brief Représente les liens entre les noeuds
 */
class Connexion : public QGraphicsItem, public IdentityToken
{

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit Connexion(NodeConnectable &n1, NodeConnectable &n2, const GamerList &gl);
    virtual ~Connexion();

    /*SURCHARGE*/
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void advance(int step);

    /*ASSESSEUR / MUTATEUR*/
    NodeConnectable &getNode1() const;
    NodeConnectable &getNode2() const;
    bool isConnextedTo(NodeConnectable &n) const;

    void sendSquad(Squad s, int nodeId);

    /*MISE A JOUR*/
    QString getUpdateString() const;
    QString getCreationString() const;
    void updateFromString(QString &s);
    static void getCreationValue(QString &s, int &connexionId, int &node1Id, int &node2Id);
    static bool isContainsPrivateChar(QString &s);

private:
    /*ENTREE*/
    NodeConnectable &n1; ///< Point d'ancrage de la connexion
    NodeConnectable &n2; ///< Point d'ancrage de la connexion
    const GamerList &lstGamer; ///< Liste des joueurs

    /*OUTIL*/
    int distance; ///< Distance entre chaque noeud
    int pathLegth; ///< Durée en nombre de "tic" de la traversée d'un noeud a l'autre
    int counterAdvance; ///< Diviseur de tic
    QQueue<Squad *> lstSquad1To2; ///< File de transfère du noeud 1 au noeud 2
    QQueue<Squad *> lstSquad2To1; ///< File de transfère du noeud 2 au noeud 1
    const double stepMultiplier; ///< Augmante l'avance des squads dans la connexion


    /*METHODE PRIVE*/
    void advanceSquad();
    void resolveSquadFigth();
    void checkSquadArrive();
    QList<QPair<Squad *, Squad *> > checkSquadColision();
    void squadPatern(QPainter *painter, Squad *s);
};

#endif // CONNEXION_H
