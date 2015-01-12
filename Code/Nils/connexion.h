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
 * @brief Représente les liens entre les noeuds
 */
class Connexion : public QGraphicsObject, public IdentityToken
{
    Q_OBJECT
public:
    /*STATIC*/
    static Connexion * getConnexion(int idConnexion);

    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit Connexion(Node &n1, Node &n2, QGraphicsItem *parent=0);
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

    /*PARSING*/
    QString getUpdateString();
    void updateFromString(QString &s);
private:
    /*INPUT*/
    Node &n1;
    Node &n2;
    int pathLength;

    /*TOOL*/
    QQueue<Squad *> lstSquad1To2;
    QQueue<Squad *> lstSquad2To1;
    int counterAdvance;

    /*METHODE PRIVE*/
    void advanceSquad();
    void resolveSquadFigth();
    void checkSquadArrive();
    QList<QPair<Squad *, Squad *> > checkSquadColision();
};

#endif // CONNEXION_H
