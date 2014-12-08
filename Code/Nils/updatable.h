#ifndef UPDATABLE_H
#define UPDATABLE_H

#include <QObject>

/**
 * @brief Super classe abstraite de tout les objets
 * devant être mis à jour lors de la boucle de
 * rafraichissement
 */
class Updatable : public QObject
{
    Q_OBJECT
public:
    explicit Updatable(QObject *parent = 0);

private:
    virtual void tic();
};

#endif // UPDATABLE_H
