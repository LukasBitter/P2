#ifndef GAMER_H
#define GAMER_H

#include <QColor>
#include <QObject>
#include "identitytoken.h"

class QTcpSocket;

namespace GameComponent {
class Gamer;
}

/**
 * @class Gamer
 * @brief Représente un joueur de la partie
 */
class Gamer : public QObject, public IdentityToken
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit Gamer(QObject *parent=0);

    /*ASSESSEUR / MUTATEUR*/
    void setColor(QColor c);
    QColor getColor() const;
    void setSocket(QTcpSocket *s);
    QTcpSocket *getSocket() const;
    bool isReady()const;
    QString getName()const;
    void setReady(bool b);
    void setName(QString s);

    /*MISE A JOUR*/
    QString getUpdateString();
    void updateFromString(QString &s);

private:
    /*OUTIL*/
    QColor color; ///< Couleur du joueur
    QString name; ///< Nom du joueur
    bool ready; ///< Indique si le joueur est pret
    QTcpSocket * socket; ///< Socket de connexion au serveur
};

#endif // GAMER_H
