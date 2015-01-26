#include "gamescene.h"
#include "node.h"
#include "nodemana.h"
#include "connexion.h"
#include "gamer.h"
#include "gamerlist.h"
#include "global.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameScene::GameScene(GamerList &gl, const Gamer *g, QObject *parent) :
    QGraphicsScene(parent), lstGamer(gl), owner(g)
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
            Node *n = Node::createNode(s, lstGamer);

            addNode(*n);
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
            lstConnexion.insert(numberId, c);
            addItem(c);
        }
    }
}

GameScene::~GameScene()
{
    qDebug()<<"GameScene : destroy";

    //Les connexion doivent impérativement être supprimé avant les noeud
    foreach (Connexion *c, lstConnexion)
    {
        removeItem(c);
    }
    lstConnexion.clear();

    //La scene s'occupe de detruire les noeud
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

void GameScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    const QPixmap background(":/Background.jpg");
    painter->drawPixmap(-10,-10, background);
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

Node *GameScene::getNode(int idNode)
{
    //qDebug()<<"GameScene : enter 'getNode'";

    return lstNode.value(idNode, 0);
}

Connexion *GameScene::getConnexion(int idConnexion)
{
    //qDebug()<<"GameScene : enter 'getConnexion'";

    return lstConnexion.value(idConnexion, 0);
}

const Gamer *GameScene::isVictory()
{
    const Gamer *g = 0;
    foreach (Node *n, lstNode)
    {
        if(n->getOwner() != 0)
        {
            if(g == 0) g = n->getOwner();
            else if(g != n->getOwner()) return 0;
        }
    }
    return g;
}

void GameScene::addNode(Node &n)
{
    qDebug()<<"GameScene : enter 'addNode'";

    NodeMana *nm = dynamic_cast <NodeMana*>(&n);

    if(nm != 0)
    {
        connect(nm, SIGNAL(manaEmission(int,int)), this, SLOT(onManaEmission(int,int)));
    }

    lstNode.insert(n.getId(),&n);
    addItem(&n);
}

void GameScene::addConnexion(Node &n1, Node &n2)
{
    qDebug()<<"GameScene : enter 'addConnexion'";

    if(n1.getId() == n2.getId()) return;

    if(lstNode.contains(n1.getId()) &&
            lstNode.contains(n2.getId()))
    {
        Connexion *c = new Connexion(n1, n2, lstGamer);
        lstConnexion.insert(c->getId(),c);
        addItem(c);
    }
}

void GameScene::removeNode(Node &n)
{
    qDebug()<<"GameScene : enter 'removeNode'";

    foreach (Connexion *c, n.getConnexions())
    {
        lstConnexion.remove(c->getId());
        removeItem(c);
    }
    lstNode.remove(n.getId());
    removeItem(&n);
}

void GameScene::removeConnexion(Node &n1, Node &n2)
{
    qDebug()<<"GameScene : enter 'removeConnexion'";

    Connexion *c = n1.getConnexion(n2.getId());
    lstConnexion.remove(c->getId());
    removeItem(c);
}

/*----------------------------------------------------*/
/*MISE A JOUR*/
/*----------------------------------------------------*/

QString GameScene::getUpdateString()
{
    //qDebug()<<"GameScene : enter 'getUpdateString'";

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
    //qDebug()<<"GameScene : enter 'getCreationString'";

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

QStringList GameScene::normalizeSpawn()
{
    QStringList spawnList;
    foreach (Node *n, lstNode)
    {
        if(n->getOwner() != 0)
        {
            spawnList.append(QString(".@%1.%2").arg(n->getId()).arg(n->normalizeSpawn()));
            n->setOwner(0);
        }
    }
    return spawnList;
}

bool GameScene::isContainsPrivateChar(QString &s)
{
    return s.contains("@") || s.contains(".") || s.contains("/");
}

void GameScene::onManaEmission(int gamerId, int mana)
{
    emit manaEmission(gamerId, mana);
}

void GameScene::updateFromString(QString s)
{
    //qDebug()<<"GameScene : enter 'updateFromString'";

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
                if(c != 0) c->updateFromString(data);
                else qCritical()<<"GameScene : unexpected case in 'updateFromString' (3)";
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
                if(n != 0) n->updateFromString(data);
                else qCritical()<<"GameScene : unexpected case in 'updateFromString' (4)";
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
