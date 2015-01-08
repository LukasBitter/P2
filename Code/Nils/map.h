#ifndef MAP_H
#define MAP_H

#include <QMap>
#include <QWidget>
#include <QGraphicsView>
#include "connexion.h"

class QGraphicsScene;
class Node;
class Connexion;

namespace GameComponent {
    class Map;
}

class Map: public QGraphicsView
{
    Q_OBJECT
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit Map(QWidget *parent=0);
    virtual ~Map();


    /*ASSESSEUR / MUTATEUR*/
    void addNode(Node &n);
    bool addConnexion(Node &n1, Node &n2);
    int getTotalRessources(Gamer &g);
    int getAvrageRessourcesRate(Gamer &g);
    int getTotalRessources();
    int getAvrageRessourcesRate();
    const QList<Connexion *> & getLstConnexion()const;
    const QList<Node *> & getLstNode()const;

public slots:
    void advance();

protected:

    /*SURCHARGE*/
    void keyPressEvent(QKeyEvent *e);

private:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    //Ne pas implementer, les copies ne sont pas voulues
    Map(Map &c);
    Map& operator=(const Map&);

    /*TOOL*/
    QGraphicsScene * scene;
    QList<Node *> lstNode;
    QList<Connexion *> lstConnexion;
    Node *currentSelection;
    Node *lastSelection;

    /*METHODE PRIVE*/
    void getPath(Node &n1, Node &n2)const;
    int sortNodeByWight(const QPair<int, int> *a, const QPair<int, int> *b);

private slots:
    void selectionChange();

};

#endif // MAP_H
