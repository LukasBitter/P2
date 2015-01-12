#ifndef GAMERINTERFACE_H
#define GAMERINTERFACE_H

#include <QGraphicsObject>

class QRadioButton;
class QPushButton;

class GamerInterface : public QGraphicsObject
{
public:
    GamerInterface();
    ~GamerInterface();

private:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    //Ne pas implementer, les copies ne sont pas voulues
    GamerInterface(GamerInterface &c);
    GamerInterface& operator=(const GamerInterface&);

    QPushButton *btPower1;
    QPushButton *btPower2;
    QPushButton *btPower3;
    QPushButton *btPower4;
    QPushButton *btPower5;
};

#endif // GAMERINTERFACE_H
