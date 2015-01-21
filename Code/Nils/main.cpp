#include <QApplication>
#include "GameMenu/gamemenumanager.h"
#include "GameComponent/gameview.h"
#include   "gamerlist.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    GamerList f;
//    GameView v("10.3.4/8.6.4/9.5.3/7.6.3/@6.300.300.50.110.-1/4.500.500.30.100.2/5.400.200.10.10.-1/3.300.100.50.100.1/",
//              f , 0, 0);
//    v.updateFromString("10.150_30_2_1,/8./9./7./@6.50,1,0,0,0/4.20,1,0,0,0/5.0,1,0,0,0/3.50,1,0,0,0/");

//    v.show();
    GameMenuManager l;
    l.show();
    return a.exec();
}
