#include "map.h"
#include "node.h"
#include "connexion.h"
#include "gamer.h"
#include "gamescene.h"
#include "GameInterface/powerinterface.h"
#include <QKeyEvent>
#include <QMouseEvent>

#include <QDropEvent>
#include <QMimeData>

#include <QDebug>


using namespace std;


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Map::Map(const Gamer *g, QWidget *parent) :
    QGraphicsView(parent), owner(g), percentToSend(100)
{
    scene = new GameScene(this);
    setScene(scene);
    scene->setSceneRect(-1000,-1000,2000,2000);

    connect(scene,SIGNAL(selectionChanged()),this,SLOT(selectionChange()));

    // Désactivation des scrollbars
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setViewportUpdateMode( QGraphicsView::BoundingRectViewportUpdate );
    setRenderHint( QPainter::Antialiasing, true );
    //setDragMode(QGraphicsView::RubberBandDrag);

    p = new PowerInterface();
    p->setX(-200);
    p->setY(-200);
    p->setMana(1000);
    scene->addItem(p);
    connect(p,SIGNAL(powerPressed(PowerName)),this,SLOT(powerPressed(PowerName)));

    currentSelection = 0;
    lastSelection = 0;
}

Map::Map(QString create, const Gamer *g, QWidget *parent):
    Map(g, parent)
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

                Node *n = new Node(posX, posY, radius,ressourcesMax,
                                   Gamer::getGamer(ownerId));
                n->setId(numberId);
                addNode(*n);
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

                Node *n1 = Node::getNode(idNode1);
                Node *n2 = Node::getNode(idNode2);
                Connexion *c = new Connexion(*n1, *n2);
                c->setId(numberId);

                n1->addConnexion(c);
                n2->addConnexion(c);
                lstConnexion.insert(c->getId(), c);
                scene->addItem(c);
            }
        }
    }
}

Map::~Map()
{
    //Efface simplement la liste des pointeurs
    lstNode.clear();
    //La scene s'occupe de detruire les noeud et les connexions
    delete scene;
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void Map::keyPressEvent(QKeyEvent *e)
{
    QGraphicsView::keyPressEvent(e);
    if(e->key() == Qt::Key_Space &&
            currentSelection != 0 && lastSelection != 0 &&
            currentSelection != lastSelection &&
            (lastSelection->getOwner() == owner || owner==0) &&
            lastSelection->getOwner() !=0)
    {
        sendSquad(lastSelection->getId(), currentSelection->getId());
    }
}

void Map::mousePressEvent(QMouseEvent *e)
{
    if(e->button()== Qt::RightButton)
    {
        Node *n = dynamic_cast <Node*>(itemAt(e->pos()));
        if(n != 0 && currentSelection != 0)
        {
            sendSquad(currentSelection->getId(), n->getId());
        }
    }
    QGraphicsView::mousePressEvent(e);
}
void Map::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasText())
    {
        event->accept();
        int s = qvariant_cast<QString>(event->mimeData()->text()).toInt();
        Node *n = dynamic_cast <Node*>(this->itemAt(event->pos()));
        if(n != 0)sendSquad(s, n->getId());
    }
    QGraphicsView::dropEvent(event);
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

void Map::addNode(Node &n)
{
    n.setZValue(10);
    lstNode.insert(n.getId(),&n);
    scene->addItem(&n);
}

void Map::addConnexion(Node &n1, Node &n2)
{
    n1.connect(n2);
    Connexion *c = n1.getConnexion(n2);
    c->setZValue(1);
    lstConnexion.insert(c->getId(),c);
    scene->addItem(c);
}

int Map::getTotalRessources(Gamer &g)
{
    int total = 0;
    foreach (Node *n, lstNode)
    {
        if(n->getOwner() == &g)total += n->getRessources();
    }
    return total;
}

int Map::getAvrageRessourcesRate(Gamer &g)
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

int Map::getTotalRessources()
{
    int total = 0;
    foreach (Node *n, lstNode)
    {
        total += n->getRessources();
    }
    return total;
}

int Map::getAvrageRessourcesRate()
{
    int sum = 0;
    foreach (Node *n, lstNode)
    {
        sum += n->getRessourcesRate();
    }
    return sum / lstNode.size();
}

void Map::setPercentToSend(int percent)
{
    if(percent>=0 && percent<=100) percentToSend = percent;
}

/*----------------------------------------------------*/
/*MISE A JOUR*/
/*----------------------------------------------------*/

QString Map::getUpdateString()
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

void Map::updateFromString(QString &s)
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
                Connexion *c = Connexion::getConnexion(numberId);
                c->updateFromString(data);
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
                Node *n = Node::getNode(numberId);
                n->updateFromString(data);
            }
        }
    }
}

QString Map::getCreationString()
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
                 arg(n->getPosX()).
                 arg(n->getPosY()).
                 arg(n->getRadius()).
                 arg(n->getRessourcesMax()).
                 arg(id));
    }
    return s;
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void Map::advance()
{
    scene->advance();
}

void Map::powerPressed(PowerName n)
{
    switch (n) {
    case Destroy:
        if(currentSelection != 0 && currentSelection->getOwner() != owner)
        {
            p->usePowerDestroy(currentSelection);
        }
        break;
    case Invincibility:
        if(currentSelection != 0 && currentSelection->getOwner() == owner)
        {
            p->usePowerInvincibility(currentSelection);
        }
        break;
    case Armore:
        if(currentSelection != 0 && currentSelection->getOwner() == owner)
        {
            p->usePowerArmore(currentSelection);
        }
        break;
    case Teleportation:
        if(currentSelection != 0 && lastSelection != 0 && lastSelection->getOwner() == owner)
        {
            p->usePowerTeleportation(lastSelection, currentSelection);
        }
        break;
    default:
        break;
    }
}

void Map::selectionChange()
{
    lastSelection = currentSelection;
    QList<QGraphicsItem *> lst = scene->selectedItems();
    if(!lst.isEmpty())
    {
        currentSelection = dynamic_cast <Node*>(lst.first());
    }
    else
    {
        currentSelection = 0;
    }
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void Map::sendSquad(int nodeIdFrom, int nodeIdTo)
{
    if(!lstNode.isEmpty())
    {
        Node *nodeFrom = lstNode.value(nodeIdFrom);
        Node *nodeTo = lstNode.value(nodeIdTo);
        int nbRessource = nodeFrom->getRessources()*(int)(percentToSend/100);

        if(nodeFrom != 0 && nodeTo != 0 &&
                nodeFrom->getOwner() == owner)
        {
            nodeFrom->sendSquad(nbRessource, *nodeTo);
        }
    }
}


