#ifndef MAP_H
#define MAP_H
#include <QWidget>
#include <QGraphicsView>
#include "connexion.h"
#include "power.h"

class GameScene;
class Node;
class Connexion;
class QDropEvent;

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
    void mousePressEvent(QMouseEvent *event);
    void dropEvent(QDropEvent *event);

    /*ASSESSEUR / MUTATEUR*/
    void addNode(Node &n);
    bool addConnexion(Node &n1, Node &n2);
    int getTotalRessources(Gamer &g);
    int getAvrageRessourcesRate(Gamer &g);
    int getTotalRessources();
    int getAvrageRessourcesRate();
    void setPercentToSend(int percent);

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
    GameScene * scene;
    QHash<int, Node *> lstNode;
    QHash<int, Connexion *> lstConnexion;
    Node *currentSelection;
    Node *lastSelection;
    Power power;
    float percentToSend;

private slots:
    void selectionChange();
    void sendSquad(int nodeIdFrom, int nodeIdTo);
};

#endif // MAP_H
