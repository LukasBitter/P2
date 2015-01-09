#ifndef MAP_H
#define MAP_H

#include <QMap>
#include <QWidget>
#include <QGraphicsView>
#include "connexion.h"
#include "power.h"

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
    explicit Map(const Gamer *g = 0, QWidget *parent=0);
    explicit Map(QString update, const Gamer *g = 0, QWidget *parent=0);
    virtual ~Map();

    /*SURCHARGE*/
    void keyPressEvent(QKeyEvent *e);

    /*ASSESSEUR / MUTATEUR*/
    void addNode(Node &n);
    bool addConnexion(Node &n1, Node &n2);
    int getTotalRessources(Gamer &g);
    int getAvrageRessourcesRate(Gamer &g);
    int getTotalRessources();
    int getAvrageRessourcesRate();
    const QList<Connexion *> & getLstConnexion()const;
    const QList<Node *> & getLstNode()const;

    /*PARSING*/
    QString getUpdateString();
    void updateFromString(QString &s);
    QString getCreationString();
public slots:
    void advance();

protected:


private:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    //Ne pas implementer, les copies ne sont pas voulues
    Map(Map &c);
    Map& operator=(const Map&);

    /*INPUT*/
    const Gamer *owner;

    /*TOOL*/
    QGraphicsScene * scene;
    QList<Node *> lstNode;
    QList<Connexion *> lstConnexion;
    Node *currentSelection;
    Node *lastSelection;
    Power power;

private slots:
    void selectionChange();

};

#endif // MAP_H
