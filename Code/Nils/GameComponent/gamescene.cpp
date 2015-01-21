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
        QStringList allConnexionsStr =
                allNodesAndConnexions.first().split("/");
        allNodesAndConnexions.pop_front();
        QStringList allNodesStr =
                allNodesAndConnexions.first().split("/");

        foreach (QString s, allNodesStr)
        {
            Node *n = new Node(s, lstGamer);
            addNode(*n);
            qDebug()<<lstNode.size();
        }

        foreach (QString s, allConnexionsStr)
        {
            int numberId;
            int idNode1;
            int idNode2;
            Connexion::getCreationValue(s,numberId,idNode1,idNode2);

            Node *n1 = getNode(idNode1);
            Node *n2 = getNode(idNode2);
            Connexion *c = new Connexion(*n1, *n2, lstGamer);
            c->setId(numberId);

            n1->connect(idNode2,c);
            n2->connect(idNode1,c);
            lstConnexion.insert(numberId, c);
            addItem(c);
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
    lstNode.insert(n.getId(),&n);
    addItem(&n);
}

void GameScene::addConnexion(Node &n1, Node &n2)
{
    if(lstNode.contains(n1.getId()) &&
            lstNode.contains(n2.getId()))
    {
        Connexion *c = new Connexion(n1, n2, lstGamer);
        n1.connect(n2.getId(), c);
        n2.connect(n1.getId(), c);
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
    s.resize(s.size()-1);
    s.append("@");
    foreach (Node *n, lstNode)
    {
        s.append(QString("%1.%2/").arg(n->getId()).arg(n->getUpdateString()));
    }
    s.resize(s.size()-1);
    return s;
}

QString GameScene::getCreationString()
{
    QString s;
    foreach (Connexion *c, lstConnexion)
    {
        s.append(QString("%1/").arg(c->getCreationString()));
    }
    s.resize(s.size()-1);
    s.append("@");
    foreach (Node *n, lstNode)
    {
        s.append(QString("%1/").arg(n->getCreationString()));
    }
    s.resize(s.size()-1);
    return s;
}

void GameScene::updateFromString(QString &s)
{
    QStringList allNodesAndConnexions = s.split("@");
    if(allNodesAndConnexions.size() == 2)
    {
        QStringList allConnexionsStr =
                allNodesAndConnexions.first().split("/");
        allNodesAndConnexions.pop_front();
        QStringList allNodesStr =
                allNodesAndConnexions.first().split("/");

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
            else
            {
                qCritical()<<"GameScene : unexpected case in 'updateFromString' (1)";
            }
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
            else
            {
                qCritical()<<"GameScene : unexpected case in 'updateFromString' (2)";
            }
        }
    }
    else
    {
        qCritical()<<"GameScene : unexpected case in 'updateFromString' (3)";
    }
}
