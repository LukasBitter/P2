#include <QApplication>
#include "GameMenu/gamemenumanager.h"
#include "GameComponent/gameview.h"
#include "gamerlist.h"
#include "global.h"

#include "GameComponent/gamescene.h"
#include "GameComponent/nodecombat.h"

void createGame()
{
    GamerList l;
    GameView s(l);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    createGame();
//    return 0;


    GameMenuManager l;
    l.show();
    return a.exec();
}
