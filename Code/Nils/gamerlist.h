#ifndef GAMERLIST_H
#define GAMERLIST_H

#include <QHash>

class Gamer;
class QString;
class QTcpSocket;
class QColor;

class GamerList
{
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit GamerList();
    ~GamerList();

    /*ASSESSEUR / MUTATEUR*/
    const QHash<int,Gamer *> & getLstGamer();
    Gamer * getGamer(int idGamer);
    Gamer * getGamer(QTcpSocket *socket);
    bool isNameExist(QString s);
    void addGamer(Gamer* g);

    /*MISE A JOUR*/
    QString getLstGamerUpdateString();
    void updateLstGamerFromString(QString &s);

private:
    /*OUTIL*/
    QHash<int,Gamer *> lstGamers;
    QList<QColor> lstColor;

    /*METHODE PRIVE*/
    QColor getNextColor();
};

#endif // GAMERLIST_H
