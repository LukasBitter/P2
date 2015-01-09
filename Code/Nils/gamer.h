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
    static Gamer * getGamer(int idGamer);

    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit Gamer(QColor color, QObject *parent=0);
    virtual ~Gamer();

    /*ASSESSEUR / MUTATEUR*/
    QColor getColor() const;
private:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    //Ne pas implementer, les copies ne sont pas voulues
    Gamer(Gamer &c);
    Gamer& operator=(const Gamer&);

    /*TOOL*/
    QColor color;
};

#endif // GAMER_H
