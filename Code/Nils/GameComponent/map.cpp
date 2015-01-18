#include "map.h"
#include "node.h"
#include "connexion.h"
#include "gamer.h"
#include "gamerlist.h"
#include "gamescene.h"
#include "GameInterface/powerinterface.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Map::Map(const Gamer *g, QWidget *parent) :
    QGraphicsView(parent), owner(g), percentToSend(100), scene(0),
    lastSelection(0),currentSelection(0), ui(0)
{
    setUpUI();
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
                                   GamerList::getGamer(ownerId));
                n->setId(numberId);
                addNode(*n);
            }
            else
            {
                qCritical()<<"Map : unexpected case in 'Map' when create nodes";
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
                Connexion *c = new Connexion(*n1, *n2);
                c->setId(numberId);

                n1->addConnexion(c);
                n2->addConnexion(c);
                lstConnexion.insert(c->getId(), c);
                scene->addItem(c);
            }
            else
            {
                qCritical()<<"Map : unexpected case in 'Map' when create connexions";
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
    if(lstNode.contains(n1.getId()) &&
            lstNode.contains(n2.getId()))
    {
        n1.connect(n2);
        Connexion *c = n1.getConnexion(n2);
        c->setZValue(1);
        lstConnexion.insert(c->getId(),c);
        scene->addItem(c);
    }
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
                Connexion *c = getConnexion(numberId);
                c->updateFromString(data);
            }
            else
            {
                qCritical()<<"Map : unexpected case in 'updateFromString' when update connexions";
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
                qCritical()<<"Map : unexpected case in 'updateFromString' when update nodes";
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
                 arg(n->x()).
                 arg(n->y()).
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

void Map::powerPressed(POWER_NAME n)
{
    qDebug()<<"Map : enter 'powerPressed'";
    switch (n) {
    case P_DESTROY:
        if(currentSelection != 0 && currentSelection->getOwner() != owner)
        {
            qDebug()<<"Map : use of P_DESTROY";
            ui->usePowerDestroy(currentSelection);
        }
        break;
    case P_INVINCIBILITY:
        qDebug()<<"Map : use of P_INVINCIBILITY";
        if(currentSelection != 0 && currentSelection->getOwner() == owner)
        {
            ui->usePowerInvincibility(currentSelection);
        }
        break;
    case P_ARMORE:
        qDebug()<<"Map : use of P_ARMORE";
        if(currentSelection != 0 && currentSelection->getOwner() == owner)
        {
            ui->usePowerArmore(currentSelection);
        }
        break;
    case P_TELEPORTATION:
        qDebug()<<"Map : use of P_TELEPORTATION";
        if(currentSelection != 0 && lastSelection != 0 && lastSelection->getOwner() == owner)
        {
            ui->usePowerTeleportation(lastSelection, currentSelection);
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

Node *Map::getNode(int idNode)
{
    if(lstNode.contains(idNode))
    {
        return lstNode.value(idNode);
    }
    else
    {
        qWarning()<<"Map : 'getNode' return a null pointer";
        return 0;
    }
}

Connexion *Map::getConnexion(int idConnexion)
{
    if(lstConnexion.contains(idConnexion))
    {
        return lstConnexion.value(idConnexion);
    }
    else
    {
        qWarning()<<"Map : 'getConnexion' return a null pointer";
        return 0;
    }
}

void Map::setUpUI()
{
    scene = new GameScene(this);
    setScene(scene);
    connect(scene,SIGNAL(selectionChanged()),this,SLOT(selectionChange()));

    // Désactivation des scrollbars
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setViewportUpdateMode( QGraphicsView::BoundingRectViewportUpdate );
    setRenderHint( QPainter::Antialiasing, true );
    //setDragMode(QGraphicsView::RubberBandDrag);

    ui = new PowerInterface();
    ui->setX(-200);
    ui->setY(-200);
    ui->setMana(1000);
    scene->addItem(ui);
    connect(ui,SIGNAL(powerPressed(POWER_NAME)),this,SLOT(powerPressed(POWER_NAME)));
}
