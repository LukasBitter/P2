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

namespace GameComponent {
class Connexion;
}

/**
 * @class Connexion
 * @brief Représente les liens entre les noeuds
 */
class Connexion : public QGraphicsObject, public IdentityToken
{
    Q_OBJECT

public:
    /*METHODE DE CLASSE*/
    static Connexion * getConnexion(int idConnexion);

    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit Connexion(Node &n1, Node &n2);
    virtual ~Connexion();

    /*SURCHARGE*/
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void advance(int step);

    /*ASSESSEUR / MUTATEUR*/
    Node & getNode1() const;
    Node & getNode2() const;
    bool isConnextedTo(Node &n) const;
    void sendSquad(Squad *s, Node &from);

    /*MISE A JOUR*/
    QString getUpdateString();
    void updateFromString(QString &s);

private:
    /*ENTREE*/
    Node &n1; ///< Point d'ancrage de la connexion
    Node &n2; ///< Point d'ancrage de la connexion
    int pathLength; ///< Durée en nombre de "tic" de la traversée d'un noeud a l'autre

    /*OUTIL*/
    QQueue<Squad *> lstSquad1To2; ///< File de transfère du noeud 1 au noeud 2
    QQueue<Squad *> lstSquad2To1; ///< File de transfère du noeud 2 au noeud 1
    int counterAdvance;

    /*METHODE PRIVE*/
    void advanceSquad();
    void resolveSquadFigth();
    void checkSquadArrive();
    QList<QPair<Squad *, Squad *> > checkSquadColision();
};

#endif // CONNEXION_H
