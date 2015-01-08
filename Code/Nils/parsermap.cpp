#include "parsermap.h"
#include "connexion.h"
#include "node.h"
#include "map.h"
#include <QStringBuilder>

ParserMap::ParserMap()
{
}

ParserMap::~ParserMap()
{

}

QString * ParserMap::parse(Map &m)
{
    const QList<Connexion *> &lstC = m.getLstConnexion();
    const QList<Node *> &lstN = m.getLstNode();

    foreach (Connexion *c, lstC)
    {

    }
}

void ParserMap::unParse(QString &s, Map &m)
{

}
