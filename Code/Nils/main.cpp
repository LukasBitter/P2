#include "GameComponent/map.h"
#include "GameComponent/gamer.h"
#include "GameComponent/node.h"
#include "GameConnexion/server.h"
#include "GameConnexion/client.h"
#include <QtWidgets>
#include <QApplication>
#include <qdebug.h>
#include "GameMenu/gamemenumanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameMenuManager l;
    l.show();
    return a.exec();
}
