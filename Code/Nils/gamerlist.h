#ifndef GAMERLIST_H
#define GAMERLIST_H

#include <QHash>

class Gamer;
class QString;
class QTcpSocket;
class QColor;

/**
 * @class GamerList
 * @brief Liste des joueur présent dans la partie
 */
class GamerList
{
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit GamerList();
    ~GamerList();

    /*ASSESSEUR / MUTATEUR*/
    const QHash<int,Gamer *> & getLstGamer()const;
    Gamer * getGamer(int idGamer) const;
    Gamer * getGamer(QTcpSocket *socket)const;
    bool isNameExist(const QString &s)const;

    void addGamer(Gamer* g);

    /*MISE A JOUR*/
    QString getLstGamerUpdateString()const;
    void updateLstGamerFromString(const QString &s);

private:
    /*OUTIL*/
    QHash<int,Gamer *> lstGamers; ///< Liste interne des joueurs présents
};

#endif // GAMERLIST_H
