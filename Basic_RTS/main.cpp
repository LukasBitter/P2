#include <QApplication>
#include "GameMenu/gamemenumanager.h"
#include "enumlibrary.h"
#include "settings.h"


int main(int argc, char *argv[])
{
    QDir d(MAP_FILE);

    if(!d.exists())
    {
        d.mkpath(".");
    }

    QFile c(CONFIG_FILE);

    if(!c.exists())
    {
        createDefaultSettingFile();
    }

    loadSettingFromFile();

    QApplication a(argc, argv);

    GameMenuManager l;
    l.show();

    return a.exec();
}
