#ifndef GAMERLIST_H
#define GAMERLIST_H

#include <QHash>

class Gamer;
class QString;
class QTcpSocket;

class GamerList
{
public:
    /*METHODE DE CLASSE*/
    static const QHash<int,Gamer *> & getLstGamer();
    static Gamer * getGamer(int idGamer);
    static Gamer * getGamer(QTcpSocket *socket);
    static bool isNameExist(QString s);
    static QString getLstGamerUpdateString();
    static void updateLstGamerFromString(QString &s);
    static void clearGamerList();
    static void addGamer(Gamer* g);
};

#endif // GAMERLIST_H
