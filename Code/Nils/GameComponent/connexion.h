#ifndef CONNEXION_H
#define CONNEXION_H

#include <QGraphicsObject>
#include <QQueue>
#include "identitytoken.h"

class Node;
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
    explicit Connexion(Node &n1, Node &n2, const GamerList &gl);
    virtual ~Connexion();

    /*SURCHARGE*/
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void advance(int step);

    /*ASSESSEUR / MUTATEUR*/
    Node &getNode1() const;
    Node &getNode2() const;
    bool isConnextedTo(Node &n) const;

    void sendSquad(Squad s, int nodeId);

    /*MISE A JOUR*/
    QString getUpdateString() const;
    QString getCreationString() const;
    void updateFromString(QString &s);
    static void getCreationValue(QString &s, int &connexionId, int &node1Id, int &node2Id);
    static bool isContainsPrivateChar(QString &s);

private:
    /*ENTREE*/
    Node &n1; ///< Point d'ancrage de la connexion
    Node &n2; ///< Point d'ancrage de la connexion
    const GamerList &lstGamer; ///< Liste des joueurs

    /*OUTIL*/
    int pathLength; ///< Durée en nombre de "tic" de la traversée d'un noeud a l'autre
    int counterAdvance; ///< Diviseur de tic
    QQueue<Squad *> lstSquad1To2; ///< File de transfère du noeud 1 au noeud 2
    QQueue<Squad *> lstSquad2To1; ///< File de transfère du noeud 2 au noeud 1


    /*METHODE PRIVE*/
    void advanceSquad();
    void resolveSquadFigth();
    void checkSquadArrive();
    QList<QPair<Squad *, Squad *> > checkSquadColision();
};

#endif // CONNEXION_H
