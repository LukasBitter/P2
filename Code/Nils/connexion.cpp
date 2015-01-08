#include "connexion.h"
#include "node.h"
#include "gamer.h"
#include "squad.h"
#include <QPainter>
#include <QtMath>

#include <QDebug>

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Connexion::Connexion(Node &n1, Node &n2, QGraphicsItem *parent)
    : QGraphicsObject(parent), n1(n1), n2(n2)
{
    qreal dist = sqrt(pow(abs(n1.getPosX()-n2.getPosX()),2)+
                      pow(abs(n1.getPosY()-n2.getPosY()),2));
    pathLength = dist;
    setNextId();
}

Connexion::~Connexion()
{
    qDeleteAll(lstSquad1To2);
    lstSquad1To2.clear();
    qDeleteAll(lstSquad2To1);
    lstSquad2To1.clear();
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

QRectF Connexion::boundingRect() const
{
    return QRectF(n1.getPosX(), n1.getPosY(), n2.getPosX()-n1.getPosX(), n2.getPosY()-n1.getPosY());
}

void Connexion::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    painter->save();
    painter->translate(n1.getPosX(), n1.getPosY());
    qreal angle = qRadiansToDegrees(qAtan2(n1.getPosY()-n2.getPosY(),n1.getPosX()-n2.getPosX()))+90;
    painter->rotate(angle);
    painter->drawLine(0, n1.getRadius(), 0, pathLength-n2.getRadius());

    foreach(Squad *s, lstSquad1To2)
    {
        painter->setBrush(s->getOwner().getColor());
        QPointF  p[3];
        p[0]=QPointF(-5,s->getProgress());
        p[1]=QPointF(0,s->getProgress()+5);
        p[2]=QPointF(5,s->getProgress());
        painter->drawConvexPolygon( p, 3);
    }
    foreach(Squad *s, lstSquad2To1)
    {
        painter->setBrush(s->getOwner().getColor());
        QPointF  p[3];
        p[0]=QPointF(-5,s->getProgress());
        p[1]=QPointF(0,s->getProgress()-5);
        p[2]=QPointF(5,s->getProgress());
        painter->drawConvexPolygon( p, 3);
    }
    painter->restore();
}

void Connexion::advance(int step)
{
    if(step == 0) return;

    advanceSquad();
    resolveSquadFigth();
    checkSquadArrive();
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
    return &n == &n1 || &n == &n2;
}

void Connexion::sendSquad(Squad &s, Node &from)
{
    if(&from == &n1)
    {
        s.setProgress(n1.getRadius());
        lstSquad1To2.push_front(&s);
    }
    else if(&from == &n2)
    {
        s.setProgress(pathLength-n2.getRadius());
        lstSquad2To1.push_front(&s);
    }
}

QString Connexion::getUpdateString()
{
    QString s;
    foreach (Squad *s1to2, lstSquad1To2)
    {
        s.append(QString("%1-%2-%3-0,").arg(s1to2->getProgress()).
                 arg(s1to2->getNbRessources()).arg(s1to2->getOwner().getId()));
    }
    foreach (Squad *s1to2, lstSquad2To1)
    {
        s.append(QString("%1-%2-%3-1,").arg(s1to2->getProgress()).
                 arg(s1to2->getNbRessources()).arg(s1to2->getOwner().getId()));
    }
    return s;
}

void Connexion::updateFromString(QString &s)
{
    qDeleteAll(lstSquad1To2);
    lstSquad1To2.clear();
    qDeleteAll(lstSquad2To1);
    lstSquad2To1.clear();

    QStringList lstSubStr1 = s.split(",");
    foreach (QString sub1, lstSubStr1)
    {
        QStringList lstSubStr2 = sub1.split("-");
        if(lstSubStr2.size() == 4)
        {
            QString &s1 = lstSubStr2.first();
            lstSubStr2.pop_front();
            QString &s2 = lstSubStr2.first();
            lstSubStr2.pop_front();
            QString &s3 = lstSubStr2.first();
            lstSubStr2.pop_front();
            QString &s4 = lstSubStr2.first();

            Squad *squad = new Squad(*Gamer::getGamer(s3.toInt()));
            if(s4.toInt()==0)
            {
                sendSquad(*squad, n1);
            }
            else
            {
                sendSquad(*squad, n2);
            }
            squad->setNbRessources(s2.toInt());
            squad->setProgress(s1.toInt());
        }
    }
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void Connexion::advanceSquad()
{
    foreach(Squad *s, lstSquad1To2)
    {
        int p = s->getProgress();
        if(p < pathLength-n2.getRadius())
        {
            ++p;
            s->setProgress(p);
        }
    }
    foreach(Squad *s, lstSquad2To1)
    {
        int p = s->getProgress();
        if(p > n1.getRadius())
        {
            --p;
            s->setProgress(p);
        }
    }
}

void Connexion::resolveSquadFigth()
{
    QList<QPair<Squad *, Squad *> > lstColision = checkSquadColision();

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
            delete s2;
            delete s1;
            lstSquad2To1.pop_back();
            lstSquad1To2.pop_back();
        }
    }
}


void Connexion::checkSquadArrive()
{
    foreach(Squad *s, lstSquad1To2)
    {
        int p = s->getProgress();
        if(p == pathLength-n2.getRadius())
        {
            n2.incoming(*s);
            lstSquad1To2.pop_back();
        }
    }
    foreach(Squad *s, lstSquad2To1)
    {
        int p = s->getProgress();
        if(p == n1.getRadius())
        {
            n1.incoming(*s);
            lstSquad2To1.pop_back();
        }
    }
}

QList<QPair<Squad *, Squad *> > Connexion::checkSquadColision()
{
    QList<QPair<Squad *, Squad *> > lstColision;
    foreach(Squad *s1to2, lstSquad1To2)
    {
        foreach(Squad *s2to1, lstSquad2To1)
        {
            if(abs(s1to2->getProgress()-s2to1->getProgress()) <= 1 &&
                    &s1to2->getOwner() != &s2to1->getOwner())
            {
                lstColision.append(QPair<Squad *, Squad *>(s1to2, s2to1));
            }
        }
    }
    return lstColision;
}
