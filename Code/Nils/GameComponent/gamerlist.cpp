#include "gamerlist.h"
#include "gamer.h"


/*----------------------------------------------------*/
/*METHODE DE CLASSE*/
/*----------------------------------------------------*/

QHash<int,Gamer *> lstGamers;

const QHash<int, Gamer *> &GamerList::getLstGamer()
{
    return lstGamers;
}

Gamer *GamerList::getGamer(int idGamer)
{
    if(lstGamers.contains(idGamer))
    {
        return lstGamers.value(idGamer);
    }
    else
    {
        return 0;
    }
}

Gamer *GamerList::getGamer(QTcpSocket *socket)
{
    foreach (Gamer *g, lstGamers)
    {
        if(g->getSocket() == socket) return g;
    }
    return 0;
}

bool GamerList::isNameExist(QString s)
{
    foreach (Gamer *g, lstGamers)
    {
        if(g->getName()->compare(s)) return true;
    }
    return false;
}

QString GamerList::getLstGamerUpdateString()
{
    QString s;
    foreach (Gamer *g, lstGamers)
    {
        s.append(QString("%1.%2/").arg(g->getId()).arg(g->getUpdateString()));
    }
    return s;
}

void GamerList::updateLstGamerFromString(QString &s)
{
    QStringList allGamers = s.split("/");

    foreach (QString s, allGamers)
    {
        QStringList gamerStr = s.split(".");
        if(gamerStr.size() == 2)
        {
            int numberId = gamerStr.first().toInt();
            gamerStr.pop_front();
            QString &data = gamerStr.first();

            Gamer *g = GamerList::getGamer(numberId);
            if(g == 0)
            {
                g = new Gamer();
                g->setId(numberId);
            }
            g->updateFromString(data);
        }
    }
}

void GamerList::clearGamerList()
{
    qDeleteAll(lstGamers);
    lstGamers.clear();
}

void GamerList::addGamer(Gamer *g)
{
    lstGamers.insert(g->getId(), g);
}
