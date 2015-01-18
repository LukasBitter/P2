#include "gamerlist.h"
#include "GameComponent/gamer.h"
#include <QColor>
#include <QDebug>


QHash<int,Gamer *> lstGamers;

QColor t[]= {Qt::red, Qt::blue, Qt::yellow, Qt::green};

QColor getNextColor()
{
    return t[lstGamers.size()%4];
}

/*----------------------------------------------------*/
/*METHODE DE CLASSE*/
/*----------------------------------------------------*/

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
        qWarning()<<"GamerList : 'getGamer' return a null pointer";
        return 0;
    }
}

Gamer *GamerList::getGamer(QTcpSocket *socket)
{
    foreach (Gamer *g, lstGamers)
    {
        if(g->getSocket() == socket) return g;
    }
    qWarning()<<"GamerList : 'getGamer' return a null pointer";
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
    qDebug()<<"GamerList : enter 'getLstGamerUpdateString'";
    QString s;
    foreach (Gamer *g, lstGamers)
    {
        s.append(QString("%1.%2/").arg(g->getId()).arg(g->getUpdateString()));
    }
    return s;
}

void GamerList::updateLstGamerFromString(QString &s)
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

            Gamer *g = GamerList::getGamer(numberId);
            if(g == 0)
            {
                g = new Gamer();
                g->setId(numberId);
            }
            g->updateFromString(data);
        }
        else
        {
            qCritical()<<"GamerList : unexpected case in 'updateLstGamerFromString'";
        }
    }
}

void GamerList::clearGamerList()
{
    qDebug()<<"GamerList : enter 'clearGamerList'";
    qDeleteAll(lstGamers);
    lstGamers.clear();
}

void GamerList::addGamer(Gamer *g)
{
    qDebug()<<"GamerList : enter 'addGamer'";
    g->setColor(getNextColor());
    lstGamers.insert(g->getId(), g);
}
