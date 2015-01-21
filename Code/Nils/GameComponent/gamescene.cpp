#include "gamescene.h"
#include "node.h"
#include "connexion.h"
#include "gamer.h"
#include "gamerlist.h"
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameScene::GameScene(GamerList &gl, const Gamer *g, QObject *parent) :
    QGraphicsScene(parent), lstGamer(gl),owner(g)
{
    setSceneRect(0, 0, 800, 600);
}

GameScene::GameScene(QString create, GamerList &gl, const Gamer *g, QObject *parent):
    GameScene(gl,g,parent)
{
    QStringList allNodesAndConnexions = create.split("@");
    if(allNodesAndConnexions.size() == 2)
    {
        QStringList allConnexionsStr = allNodesAndConnexions.first().split("/");
        allNodesAndConnexions.pop_front();
        QStringList allNodesStr = allNodesAndConnexions.first().split("/");

        foreach (QString s, allNodesStr)
        {
            QStringList nodeStr = s.split(".");
            if(nodeStr.size() == 6)
            {
                int numberId = nodeStr.first().toInt();
                nodeStr.pop_front();
                int posX = nodeStr.first().toInt();
                nodeStr.pop_front();
                int posY = nodeStr.first().toInt();
                nodeStr.pop_front();
                int radius = nodeStr.first().toInt();
                nodeStr.pop_front();
                int ressourcesMax = nodeStr.first().toInt();
                nodeStr.pop_front();
                int ownerId = nodeStr.first().toInt();

                Node *n = new Node(posX, posY, radius,ressourcesMax,lstGamer,
                                   lstGamer.getGamer(ownerId));
                n->setId(numberId);
                addNode(*n);
            }
            else
            {
                qCritical()<<"GameScene : unexpected case in 'GameScene' when create nodes";
            }
        }

        foreach (QString s, allConnexionsStr)
        {
            QStringList connexionStr = s.split(".");
            if(connexionStr.size() == 3)
            {
                int numberId = connexionStr.first().toInt();
                connexionStr.pop_front();
                int idNode1 = connexionStr.first().toInt();
                connexionStr.pop_front();
                int idNode2 = connexionStr.first().toInt();

                Node *n1 = getNode(idNode1);
                Node *n2 = getNode(idNode2);
                Connexion *c = new Connexion(*n1, *n2, lstGamer);
                c->setId(numberId);

                n1->addConnexion(c);
                n2->addConnexion(c);
                lstConnexion.insert(c->getId(), c);
                addItem(c);
            }
            else
            {
                qCritical()<<"GameScene : unexpected case in 'GameScene' when create connexions";
            }
        }
    }
}

GameScene::~GameScene()
{
    //La scene s'occupe de detruire les noeud et les connexions
    //Efface simplement la liste des pointeurs
    lstNode.clear();
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void GameScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    //Pas d'appel au parent sinon sa marche pas !
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

void GameScene::addNode(Node &n)
{
    n.setZValue(10);
    lstNode.insert(n.getId(),&n);
    addItem(&n);
}

void GameScene::addConnexion(Node &n1, Node &n2)
{
    if(lstNode.contains(n1.getId()) &&
            lstNode.contains(n2.getId()))
    {
        n1.connect(n2);
        Connexion *c = n1.getConnexion(n2);
        c->setZValue(1);
        lstConnexion.insert(c->getId(),c);
        addItem(c);
    }
}

int GameScene::getTotalRessources(Gamer &g)
{
    int total = 0;
    foreach (Node *n, lstNode)
    {
        if(n->getOwner() == &g)total += n->getRessources();
    }
    return total;
}

int GameScene::getAvrageRessourcesRate(Gamer &g)
{
    int sum = 0;
    int nb = 0;
    foreach (Node *n, lstNode)
    {
        if(n->getOwner() == &g)sum += n->getRessourcesRate();
        ++nb;
    }
    return sum / nb;
}

int GameScene::getTotalRessources()
{
    int total = 0;
    foreach (Node *n, lstNode)
    {
        total += n->getRessources();
    }
    return total;
}

int GameScene::getAvrageRessourcesRate()
{
    int sum = 0;
    foreach (Node *n, lstNode)
    {
        sum += n->getRessourcesRate();
    }
    return sum / lstNode.size();
}

Node *GameScene::getNode(int idNode)
{
    if(lstNode.contains(idNode))
    {
        return lstNode.value(idNode);
    }
    else
    {
        qWarning()<<"GameScene : 'getNode' return a null pointer";
        return 0;
    }
}

Connexion *GameScene::getConnexion(int idConnexion)
{
    if(lstConnexion.contains(idConnexion))
    {
        return lstConnexion.value(idConnexion);
    }
    else
    {
        qWarning()<<"GameScene : 'getConnexion' return a null pointer";
        return 0;
    }
}

/*----------------------------------------------------*/
/*MISE A JOUR*/
/*----------------------------------------------------*/

QString GameScene::getUpdateString()
{
    QString s;
    foreach (Connexion *c, lstConnexion)
    {
        s.append(QString("%1.%2/").arg(c->getId()).arg(c->getUpdateString()));
    }
    s.append("@");
    foreach (Node *n, lstNode)
    {
        s.append(QString("%1.%2/").arg(n->getId()).arg(n->getUpdateString()));
    }
    return s;
}

void GameScene::updateFromString(QString &s)
{
    QStringList allNodesAndConnexions = s.split("@");
    if(allNodesAndConnexions.size() == 2)
    {
        QStringList allConnexionsStr = allNodesAndConnexions.first().split("/");
        allNodesAndConnexions.pop_front();
        QStringList allNodesStr = allNodesAndConnexions.first().split("/");

        foreach (QString s, allConnexionsStr)
        {
            QStringList connexionStr = s.split(".");
            if(connexionStr.size() == 2)
            {
                int numberId = connexionStr.first().toInt();
                connexionStr.pop_front();
                QString &data = connexionStr.first();
                Connexion *c = getConnexion(numberId);
                c->updateFromString(data);
            }
            //Pas de critical ici, car VIRGULE!
        }

        foreach (QString s, allNodesStr)
        {
            QStringList nodeStr = s.split(".");
            if(nodeStr.size() == 2)
            {
                int numberId = nodeStr.first().toInt();
                nodeStr.pop_front();
                QString &data = nodeStr.first();
                Node *n = getNode(numberId);
                n->updateFromString(data);
            }
            //Pas de critical ici, car VIRGULE!
        }
    }
}

QString GameScene::getCreationString()
{
    QString s;
    foreach (Connexion *c, lstConnexion)
    {
        s.append(QString("%1.%2.%3/").arg(c->getId()).
                 arg(c->getNode1().getId()).
                 arg(c->getNode2().getId()));
    }
    s.append("@");
    foreach (Node *n, lstNode)
    {
        int id = -1;
        if(n->getOwner()!= 0)id = n->getOwner()->getId();
        s.append(QString("%1.%2.%3.%4.%5.%6/").arg(n->getId()).
                 arg(n->x()).
                 arg(n->y()).
                 arg(n->getRadius()).
                 arg(n->getRessourcesMax()).
                 arg(id));
    }
    return s;
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/
