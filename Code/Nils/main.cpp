#include <QApplication>
#include "GameMenu/gamemenumanager.h"
#include "mapfile.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MapFile m;
    m.loadFromFile("D:/Users/nils.ryter/Desktop/Code/maps/1.rtsmap");
    qDebug()<< m.isValide();
    qDebug()<< m.getVersion();
    qDebug()<< m.getCreationString();
    qDebug()<< m.getUpdateString();
    qDebug()<< m.getNumberOfSlot();
    qDebug()<< m.getSlot(0,0);
    qDebug()<< m.getSlot(1,0);
    qDebug()<< m.getSlot(2,0);
    qDebug()<< m.getSlot(3,0);
    qDebug()<< m.getSlot(4,0);
    qDebug()<<"test";
    m.saveToFile("D:/Users/nils.ryter/Desktop/Code/maps/2.rtsmap");
    GameMenuManager l;
    l.show();
    return a.exec();
}
