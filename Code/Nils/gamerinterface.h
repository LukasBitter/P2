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
    QPushButton *btPower1;
    QPushButton *btPower2;
    QPushButton *btPower3;
    QPushButton *btPower4;
    QPushButton *btPower5;
};

#endif // GAMERINTERFACE_H
