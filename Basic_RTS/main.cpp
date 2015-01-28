#include <QApplication>
#include "GameMenu/gamemenumanager.h"
#include "enumlibrary.h"


int main(int argc, char *argv[])
{
    QDir d(MAP_FILE);

    if(!d.exists())
    {
        d.mkpath(".");
    }

//    qInstallMessageHandler(logOutput);
    QApplication a(argc, argv);

    GameMenuManager l;
    l.show();
    return a.exec();
}
