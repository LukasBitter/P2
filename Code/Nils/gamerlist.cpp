#include "gamerlist.h"
#include "gamer.h"
#include <QColor>
#include <QDebug>


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GamerList::GamerList()
{
    lstColor.append(Qt::red);
    lstColor.append(Qt::green);
    lstColor.append(Qt::yellow);
    lstColor.append(Qt::blue);
}

GamerList::~GamerList()
{
    qDeleteAll(lstGamers);
    lstGamers.clear();
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

const QHash<int, Gamer *> &GamerList::getLstGamer() const
{
    return lstGamers;
}

Gamer *GamerList::getGamer(int idGamer)const
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

Gamer *GamerList::getGamer(QTcpSocket *socket) const
{
    foreach (Gamer *g, lstGamers)
    {
        if(g->getSocket() == socket) return g;
    }

    return 0;
}

bool GamerList::isNameExist(const QString &s) const
{
    foreach (Gamer *g, lstGamers)
    {
        if(g->getName().compare(s)) return true;
    }

    return false;
}

void GamerList::addGamer(Gamer *g)
{
    qDebug()<<"GamerList : enter 'addGamer'";

    lstGamers.insert(g->getId(), g);
}

/*----------------------------------------------------*/
/*MISE A JOUR*/
/*----------------------------------------------------*/

QString GamerList::getLstGamerUpdateString() const
{
    qDebug()<<"GamerList : enter 'getLstGamerUpdateString'";

    QString s;

    foreach (Gamer *g, lstGamers)
    {
        s.append(QString("%1.%2/").arg(g->getId()).arg(g->getUpdateString()));
    }

    return s;
}

void GamerList::updateLstGamerFromString(const QString &s)
{
    qDebug()<<"GamerList : enter 'updateLstGamerFromString'";

    QStringList allGamers = s.split("/");

    foreach (QString s, allGamers)
    {
        QStringList gamerStr = s.split(".");

        if(gamerStr.size() == 2)
        {
            int numberId = gamerStr.first().toInt();
            gamerStr.pop_front();
            QString &data = gamerStr.first();

            Gamer *g = getGamer(numberId);

            if(g == 0)
            {
                g = new Gamer();
                g->setId(numberId);
                addGamer(g);
            }

            g->updateFromString(data);
        }
        else
        {
            qCritical()<<"GamerList : unexpected case in 'updateLstGamerFromString'";
        }
    }
}
