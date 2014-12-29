#include "connexion.h"
#include "node.h"
#include "gamer.h"
#include "squad.h"
#include <QPainter>
#include <QtMath>
#include <QMutexLocker>

#include <QDebug>

/*
 * - Rendez thread safe toutes méthodes public implémentées
 */


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Connexion::Connexion(Node &n1, Node &n2,  QGraphicsItem *parent)
    : Connexion(n1,n2,500,parent)
{
}

Connexion::Connexion(Node &n1, Node &n2, int updateMs, QGraphicsItem *parent)
    : QGraphicsItem(parent), n1(n1), n2(n2)
{
    qreal dist = sqrt(pow(abs(n1.getPosX()-n2.getPosX()),2)+
                      pow(abs(n1.getPosY()-n2.getPosY()),2));
    pathLength = dist;
    distance = dist;

    startTimer(updateMs);
}

Connexion::~Connexion()
{
    QMutexLocker l(&lockListSquad);

    qDeleteAll(lstSquad1To2);
    lstSquad1To2.clear();
    qDeleteAll(lstSquad2To1);
    lstSquad2To1.clear();
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void Connexion::tic()
{
    advanceSquad();
    resolveSquadFigth();
    checkSquadArrive();

    QGraphicsItem::update();
}

QRectF Connexion::boundingRect() const
{
    return QRectF(n1.getPosX(), n1.getPosY(), n2.getPosX(), n2.getPosY());
}

void Connexion::paint(QPainter *painter,
                const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    painter->save();
    painter->translate(n1.getPosX(), n1.getPosY());
    qreal angle = qRadiansToDegrees(qAtan2(n1.getPosY()-n2.getPosY(),n1.getPosX()-n2.getPosX()))+90;
    painter->rotate(angle);
    painter->drawLine(0, n1.getRadius(), 0, pathLength-n2.getRadius());

    QMutexLocker l(&lockListSquad);
    foreach(Squad *s, lstSquad1To2)
    {
        painter->drawLine(-5,s->getProgress(),5,s->getProgress());
        painter->drawLine(-5,s->getProgress(),0,s->getProgress()+5);
        painter->drawLine(0,s->getProgress()+5,5,s->getProgress());
    }
    foreach(Squad *s, lstSquad2To1)
    {
        painter->drawLine(-5,s->getProgress(),5,s->getProgress());
        painter->drawLine(-5,s->getProgress(),0,s->getProgress()-5);
        painter->drawLine(0,s->getProgress()-5,5,s->getProgress());
    }
    painter->restore();
}

void Connexion::timerEvent(QTimerEvent *event)
{
    tic();
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

Node & Connexion::getNode1()const
{
    return n1;
}

Node & Connexion::getNode2()const
{
    return n2;
}

bool Connexion::isConnextedTo(Node &n) const
{
    return n.getId() == n1.getId() || n.getId() == n2.getId();
}

void Connexion::sendSquad(Squad &s, Node &from)
{
    QMutexLocker l(&lockListSquad);

    if(from.getId() == n1.getId())
    {
        s.setProgress(0);
        lstSquad1To2.push_front(&s);
    }
    else if(from.getId() == n2.getId())
    {
        s.setProgress(pathLength);
        lstSquad2To1.push_front(&s);
    }
    l.unlock();

    QGraphicsItem::update();
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void Connexion::advanceSquad()
{
    QMutexLocker l(&lockListSquad);

    foreach(Squad *s, lstSquad1To2)
    {
        int p = s->getProgress();
        if(p < pathLength)
        {
            ++p;
            s->setProgress(p);
        }
    }
    foreach(Squad *s, lstSquad2To1)
    {
        int p = s->getProgress();
        if(p > 0)
        {
            --p;
            s->setProgress(p);
        }
    }
}

void Connexion::resolveSquadFigth()
{
    QList<QPair<Squad *, Squad *> > lstColision = checkSquadColision();

    QMutexLocker m(&lockListSquad);
    QPair<Squad *, Squad *> p;
    foreach(p , lstColision)
    {
        Squad *s1 = p.first;
        Squad *s2 = p.second;
        int r1 = s1->getNbRessources();
        int r2 = s2->getNbRessources();

        if(r1 > r2)
        {
            s1->setNbRessources(r1-r2);
            delete s2;
            lstSquad2To1.pop_back();

        }
        else if(r1 < r2)
        {
            s2->setNbRessources(r2-r1);
            delete s1;
            lstSquad1To2.pop_back();
        }
        else
        {
            s1->setNbRessources(r1-r2);
            delete s2;
            lstSquad2To1.pop_back();
            s2->setNbRessources(r2-r1);
            delete s1;
            lstSquad1To2.pop_back();
        }
    }
}


void Connexion::checkSquadArrive()
{
    QMutexLocker l(&lockListSquad);

    foreach(Squad *s, lstSquad1To2)
    {
        int p = s->getProgress();
        if(p == pathLength)
        {
            n2.incoming(*s);
            lstSquad1To2.pop_back();
        }
    }
    foreach(Squad *s, lstSquad2To1)
    {
        int p = s->getProgress();
        if(p == 0)
        {
            n1.incoming(*s);
            lstSquad2To1.pop_back();
        }
    }
}

QList<QPair<Squad *, Squad *> > Connexion::checkSquadColision()
{
    QMutexLocker m(&lockListSquad);

    QList<QPair<Squad *, Squad *> > lstColision;
    foreach(Squad *s1to2, lstSquad1To2)
    {
        foreach(Squad *s2to1, lstSquad2To1)
        {
            if(abs(s1to2->getProgress()-s2to1->getProgress()) <= 1 &&
                    s1to2->getOwner().getId() != s2to1->getOwner().getId())
            {
                lstColision.append(QPair<Squad *, Squad *>(s1to2, s2to1));
            }
        }
    }
    return lstColision;
}
