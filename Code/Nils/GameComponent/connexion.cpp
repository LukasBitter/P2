#include "connexion.h"
#include "node.h"
#include "gamer.h"
#include "squad.h"
#include "gamerlist.h"
#include "global.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

/**
 * @brief Connexion::Connexion Création d'une nouvelle connexion
 * @param n1 Noeud d'ancrage de la connexion
 * @param n2 Noeud d'ancrage de la connexion
 *
 * Les connexions sont à double sens et des ressources
 * peuvent transiter du noeud 1 au noeud 2 et inversement.
 *
 * A la création un identifiant unique est défini.
 */
Connexion::Connexion(Node &n1, Node &n2, const GamerList &gl)
    : QGraphicsItem(0), n1(n1), n2(n2), lstGamer(gl)
{
    setNextId();
    setX(n1.x());
    setY(n1.y());
    setZValue(1);

    //Calcule de la distance de la connexion
    pathLength = (int)sqrt(pow(n1.x()-n2.x(),2)+
                      pow(n1.y()-n2.y(),2));
    pathLength -= n2.getRadius();
    pathLength -= n1.getRadius();

    //Connexion des noeud
    n1.connect(n2.getId(), this);
    n2.connect(n1.getId(), this);
}

Connexion::~Connexion()
{
    qDebug()<<"Connexion : destroy";

    //Efface toutes les squad présente dans la connexion
    qDeleteAll(lstSquad1To2);
    lstSquad1To2.clear();
    qDeleteAll(lstSquad2To1);
    lstSquad2To1.clear();

    //Déconnecte des noeud
    n1.disconnect(n2.getId());
    n2.disconnect(n1.getId());
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

QRectF Connexion::boundingRect() const
{
    return QRectF(0, 0, n2.x()-x(), n2.y()-y());
}

void Connexion::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    //Angle entre les 2 noeud de la connexion
    qreal angle = qRadiansToDegrees(qAtan2(n1.y()-n2.y(),n1.x()-n2.x()))+90;
    painter->rotate(angle);
    painter->translate(0, n1.getRadius());
    painter->drawLine(0, 0, 0, pathLength);

    foreach(Squad *s, lstSquad1To2)
    {
        painter->setBrush(s->getOwner().getColor());
        QPointF  p[3];
        p[0]=QPointF(-5,s->getProgress());
        p[1]=QPointF(0,s->getProgress()+5);
        p[2]=QPointF(5,s->getProgress());
        painter->drawConvexPolygon(p, 3);
    }
    painter->rotate(180);
    painter->translate(0, -pathLength);
    foreach(Squad *s, lstSquad2To1)
    {
        painter->setBrush(s->getOwner().getColor());
        QPointF  p[3];
        p[0]=QPointF(-5,s->getProgress());
        p[1]=QPointF(0,s->getProgress()+5);
        p[2]=QPointF(5,s->getProgress());
        painter->drawConvexPolygon(p, 3);
    }

    painter->restore();
}

void Connexion::advance(int step)
{
    if(step == 0) return;

    //Diviseur de tic
    if(counterAdvance < 0)
    {
        ++counterAdvance;
        return;
    }
    counterAdvance = 0;

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

/**
 * @brief Connexion::sendSquad Envoi des ressources à traver la connexion
 * @param s Squad complettement parametrée
 * @param from Noeud duquel la squad part
 *
 * En passant une squad a cette fonction, on transfère
 * également la responsabilité de la detruire à celle-ci.
 *
 * Si des squads sont ajouter et entre en collision avec une squad
 * alliée déjà présente au debut, elles fusionnent
 */
void Connexion::sendSquad(Squad s, int nodeId)
{
    QQueue<Squad *> *queue = 0;

    if(nodeId == n1.getId())
    {
        queue = &lstSquad1To2;
    }
    else if(nodeId == n2.getId())
    {
        queue = &lstSquad2To1;
    }

    if(queue != 0)
    {
        //Récupère la squad la plus proche du début
        Squad *sMin = queue->isEmpty() ? 0 : queue->last();

        if(sMin != 0 && sMin->getProgress() == 0 &&
                sMin->getOwner().getId() == s.getOwner().getId())
        {
            //Fusion des squads
            sMin->setNbRessources(sMin->getNbRessources()+s.getNbRessources());
        }
        else
        {
            //Ajout direct
            s.setProgress(0);
            queue->enqueue(new Squad(s));
        }
    }
}

/*----------------------------------------------------*/
/*MISE A JOUR*/
/*----------------------------------------------------*/

/**
 * @brief Connexion::getUpdateString
 * @return Chaine de mise a jour
 *
 * Retourne l'état de la connexion sous format texte.
 * Permet de mettre a jour une autre connexion via cette chaine.
 */
QString Connexion::getUpdateString() const
{
    QString s;
    foreach (Squad *s1to2, lstSquad1To2)
    {
        s.append(QString("%1_%2_%3_0,").arg(s1to2->getProgress()).
                 arg(s1to2->getNbRessources()).arg(s1to2->getOwner().getId()));
    }
    foreach (Squad *s1to2, lstSquad2To1)
    {
        s.append(QString("%1_%2_%3_1,").arg(s1to2->getProgress()).
                 arg(s1to2->getNbRessources()).arg(s1to2->getOwner().getId()));
    }
    s.resize(s.size()-1);
    return s;
}

QString Connexion::getCreationString() const
{
    return QString("%1,%2,%3").arg(getId()).
                     arg(n1.getId()).
                     arg(n2.getId());
}

/**
 * @brief Connexion::updateFromString
 * @param s Chaine de mise a jour
 *
 * Permet de mettre a jour la connexion via une chaine de mise a jour.
 */
void Connexion::updateFromString(QString &s)
{

    //Efface toutes les squad présente dans la connexion
    qDeleteAll(lstSquad1To2);
    lstSquad1To2.clear();
    qDeleteAll(lstSquad2To1);
    lstSquad2To1.clear();

    if(s.isEmpty()) return;

    //Recreation des squad depuis le texte de mise à jour
    QStringList allSquadsStr = s.split(",");
    foreach (QString sub1, allSquadsStr)
    {
        QStringList squadStr = sub1.split("_");
        if(squadStr.size() == 4)
        {
            int progress = squadStr.first().toInt();
            squadStr.pop_front();
            int nbRessources = squadStr.first().toInt();
            squadStr.pop_front();
            int ownerId = squadStr.first().toInt();
            squadStr.pop_front();
            int direction = squadStr.first().toInt();

            Gamer *g = lstGamer.getGamer(ownerId);
            if(g != 0)
            {
                Squad *s = new Squad(*g);
                s->setNbRessources(nbRessources);
                s->setProgress(progress);

                if(direction==0)
                {
                    lstSquad1To2.append(s);
                }
                else
                {
                    lstSquad2To1.append(s);
                }
            }
            else
            {
                qCritical()<<"Connexion : unexpected case in 'updateFromString' (1)";
            }
        }
        else
        {
            qCritical()<<"Connexion : unexpected case in 'updateFromString' (2)";
            qDebug()<<squadStr;
        }
    }
}

void Connexion::getCreationValue(QString &s, int &connexionId, int &node1Id, int &node2Id)
{
    QStringList nodeStr = s.split(",");
    if(nodeStr.size() == 3)
    {
        connexionId = nodeStr.first().toInt();
        nodeStr.pop_front();
        node1Id = nodeStr.first().toInt();
        nodeStr.pop_front();
        node2Id = nodeStr.first().toInt();
    }
    else
    {
        qCritical()<<"Connexion : unexpected case in 'getCreationValue'";
    }
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

/**
 * @brief Connexion::advanceSquad Avance toutes les squads d'un pas
 */
void Connexion::advanceSquad()
{
    foreach(Squad *s, lstSquad1To2)
    {
        int p = s->getProgress();
        ++p;
        s->setProgress(p);
    }
    foreach(Squad *s, lstSquad2To1)
    {
        int p = s->getProgress();
        ++p;
        s->setProgress(p);
    }
}

/**
 * @brief Connexion::resolveSquadFigth Resous les combat entre squad
 *
 * Les combat se produisent quand des squads ennemis sont en colision
 */
void Connexion::resolveSquadFigth()
{
    //Récupère la liste des squad en colision
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
            //S1 gagnant
            s1->setNbRessources(r1-r2);
            delete s2;
            lstSquad2To1.dequeue();

        }
        else if(r1 < r2)
        {
            //S2 gagnant
            s2->setNbRessources(r2-r1);
            delete s1;
            lstSquad1To2.dequeue();
        }
        else
        {
            //Egalité du combat
            delete s2;
            delete s1;
            lstSquad2To1.dequeue();
            lstSquad1To2.dequeue();
        }
    }
}

/**
 * @brief Connexion::checkSquadArrive Arrivée des squads
 *
 * Distribue les squad au noeud voulu quand elle
 * arrive à destination
 */
void Connexion::checkSquadArrive()
{
    foreach(Squad *s, lstSquad1To2)
    {
        if(s->getProgress() >= pathLength)
        {
            n2.incoming(*s);
            delete s;
            lstSquad1To2.dequeue();
        }
    }
    foreach(Squad *s, lstSquad2To1)
    {
        if(s->getProgress() >= pathLength)
        {
            n1.incoming(*s);
            delete s;
            lstSquad2To1.dequeue();
        }
    }
}

/**
 * @brief Connexion::checkSquadColision Recherche de squads en collision
 * @return Liste des squads en collision
 *
 * Recherche de collision entre squads allant dans le sens contraire.
 * Les collisions dans la même file ne sont pas détecté
 */
QList<QPair<Squad *, Squad *> > Connexion::checkSquadColision()
{
    QList<QPair<Squad *, Squad *> > lstColision;

    foreach(Squad *s1to2, lstSquad1To2)
    {
        foreach(Squad *s2to1, lstSquad2To1)
        {
            if(abs(s1to2->getProgress()+s2to1->getProgress()) >= pathLength &&
                    &s1to2->getOwner() != &s2to1->getOwner())
            {
                lstColision.append(QPair<Squad *, Squad *>(s1to2, s2to1));
            }
        }
    }
    return lstColision;
}
