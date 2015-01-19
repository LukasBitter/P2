#include <QApplication>
#include "GameMenu/gamemenumanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameMenuManager l;
    l.show();
    return a.exec();
}
