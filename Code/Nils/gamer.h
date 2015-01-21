#ifndef GAMER_H
#define GAMER_H

#include <QColor>
#include <QObject>
#include "GameComponent/identitytoken.h"

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
    bool isReady()const;
    QTcpSocket *getSocket() const;
    QString getName()const;
    int getSlotNumber()const;
    QColor getColor() const;

    void setColor(const QColor &c);
    void setSocket(QTcpSocket *s);
    void setReady(bool b);
    void setName(const QString &s);
    void setSlotNumber(int no);

    /*MISE A JOUR*/
    QString getUpdateString()const;
    void updateFromString(const QString &s);

private:
    /*OUTIL*/
    QColor color; ///< Couleur du joueur
    QString name; ///< Nom du joueur
    bool ready; ///< Indique si le joueur est pret
    QTcpSocket * socket; ///< Socket de connexion au serveur
    int slotNumber;
};

#endif // GAMER_H
