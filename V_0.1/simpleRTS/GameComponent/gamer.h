#ifndef GAMER_H
#define GAMER_H

#include <QColor>
#include <QObject>
#include "identitytoken.h"
#include <QHash>

namespace GameComponent {
    class Gamer;
}

/**
 * @brief Représente un joueur de la partie
 */
class Gamer : public QObject, public IdentityToken
{
    Q_OBJECT
public:
    /*STATIC*/
    static const QHash<int,Gamer *> & getLstGamer();
    static Gamer * getGamer(int idGamer);
    static QString getLstGamerUpdateString();
    static void updateLstGamerFromString(QString &s);

    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit Gamer(QObject *parent=0);
    virtual ~Gamer();

    /*ASSESSEUR / MUTATEUR*/
    void setColor(QColor c);
    QColor getColor() const;
    bool isConnected()const;
    bool isReady()const;
    QString * getName()const;
    void setConnected(bool b);
    void setReady(bool b);
    void setName(QString *s);

    /*PARSING*/
    QString getUpdateString();
    void updateFromString(QString &s);
private:

    /*TOOL*/
    QColor color;
    QString *name;
    bool connected;
    bool ready;
};

#endif // GAMER_H
