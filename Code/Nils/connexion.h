#ifndef CONNEXION_H
#define CONNEXION_H

#include <QMutex>
#include <QGraphicsObject>
#include <QQueue>

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
 *
 * Classe thread-safe
 */
class Connexion : public QGraphicsObject
{
    Q_OBJECT
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit Connexion(Node &n1, Node &n2, QGraphicsItem *parent=0);
    explicit Connexion(Node &n1, Node &n2, int updateMs, QGraphicsItem *parent=0);
    virtual ~Connexion();

    /*SURCHARGE*/
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void timerEvent( QTimerEvent * event );

    /*ASSESSEUR / MUTATEUR*/
    Node & getNode1() const;
    Node & getNode2() const;
    bool isConnextedTo(Node &n) const;
    void sendSquad(Squad &s, Node &from);

private:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    //Ne pas implementer, les copies ne sont pas voulues
    Connexion(Connexion &c);
    Connexion& operator=(const Connexion&);

    /*INPUT*/
    Node &n1;
    Node &n2;
    int pathLength;
    float distance;

    /*TOOL*/
    mutable QMutex lockListSquad;   //Sur les listes
    QQueue<Squad *> lstSquad1To2;   //Ressource critique
    QQueue<Squad *> lstSquad2To1;   //Ressource critique

    /*METHODE PRIVE*/
    void advanceSquad();
    void resolveSquadFigth();
    void checkSquadArrive();
    QList<QPair<Squad *, Squad *> > checkSquadColision();
};

#endif // CONNEXION_H
