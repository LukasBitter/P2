#include <QApplication>
#include "GameMenu/gamemenumanager.h"
#include "GameComponent/gameview.h"
#include "gamerlist.h"
#include "global.h"
#include <QtGlobal>

#include "GameComponent/gamescene.h"
#include "GameComponent/nodecombat.h"

//void logOutput(QtMsgType type, const QMessageLogContext &, const QString & str)
//{

//    switch (type)
//    {
//    case QtDebugMsg:

//        fprintf(stderr, "Debug: %s\n", str);

//        break;

//    case QtWarningMsg:

//        fprintf(stderr, "Warning : %s\n", str);

//        break;

//    case QtCriticalMsg:

//        fprintf(stderr, "Critical: %s\n", str);

//        break;

//    case QtFatalMsg:

//        fprintf(stderr, "Fatal: %s\n", str);

//        abort();

//    }
//}

int main(int argc, char *argv[])
{
//    qInstallMessageHandler(logOutput);
    QApplication a(argc, argv);

    GameMenuManager l;
    l.show();
    return a.exec();
}
