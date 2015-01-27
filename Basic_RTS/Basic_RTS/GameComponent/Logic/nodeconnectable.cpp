#include "nodeconnectable.h"
#include "connexion.h"
#include "enumlibrary.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

NodeConnectable::NodeConnectable(int x, int y, int radius): Node(x,y,radius)
{
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

void NodeConnectable::connect(int nodeId, Connexion *c)
{
    if(!mapConnexion.contains(nodeId) && nodeId != getId() &&
            (&c->getNode1() == this || &c->getNode2() == this))
    {
        mapConnexion.insert(nodeId, c);
    }
}

void NodeConnectable::disconnect(int nodeId)
{
    mapConnexion.remove(nodeId);
}

Connexion *NodeConnectable::getConnexion(int nodeId) const
{
    return mapConnexion.value(nodeId, 0);
}

QMap<int, Connexion *> NodeConnectable::getConnexions() const
{
    return mapConnexion;
}

bool NodeConnectable::isConnected(int nodeId) const
{
    return mapConnexion.contains(nodeId);
}
