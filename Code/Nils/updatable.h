#ifndef UPDATABLE_H
#define UPDATABLE_H

#include <QObject>
#include <QMutex>

namespace GameComponent {
    class Updatable;
}

class Updatable : public QObject
{
    Q_OBJECT
public:
    explicit Updatable(QObject *parent=0);
    virtual ~Updatable();
    virtual void tic() = 0;
    unsigned int getId() const;
private:
    unsigned int id;
    mutable QMutex mutex;   //Verroux sur l'objet
};

#endif // UPDATABLE_H
