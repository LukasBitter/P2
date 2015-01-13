#include "gamerinterface.h"
#include <QPushButton>
#include <QRadioButton>

GamerInterface::GamerInterface()
{
    btPower1 = new QPushButton();
    btPower2 = new QPushButton();
    btPower3 = new QPushButton();
    btPower4 = new QPushButton();
    btPower5 = new QPushButton();

}

GamerInterface::~GamerInterface()
{
    delete btPower1;
    delete btPower2;
    delete btPower3;
    delete btPower4;
    delete btPower5;
}
