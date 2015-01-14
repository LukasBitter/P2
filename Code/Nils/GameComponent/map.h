#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QGraphicsView>
#include "connexion.h"
#include "ennum.h"

class GameScene;
class Node;
class Connexion;
class QDropEvent;
class PowerInterface;

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
    void addConnexion(Node &n1, Node &n2);
    int getTotalRessources(Gamer &g);
    int getAvrageRessourcesRate(Gamer &g);
    int getTotalRessources();
    int getAvrageRessourcesRate();
    void setPercentToSend(int percent);

    /*MISE A JOUR*/
    QString getUpdateString();
    void updateFromString(QString &s);
    QString getCreationString();

    /*SIGNALS/SLOTS*/
public slots:
    void advance();
private slots:
    void powerPressed(PowerName n);
private slots:
    void selectionChange();
    void sendSquad(int nodeIdFrom, int nodeIdTo);

private:
    /*ENTREE*/
    const Gamer *owner;

    /*OUTIL*/
    GameScene * scene;
    QHash<int, Node *> lstNode;
    QHash<int, Connexion *> lstConnexion;
    Node *currentSelection;
    Node *lastSelection;
    float percentToSend;
    PowerInterface *p;

};

#endif // MAP_H
