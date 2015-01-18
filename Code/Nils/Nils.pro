QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder

TARGET = Nils
TEMPLATE = app

HEADERS += \
    GameComponent/connexion.h \
    GameComponent/gamer.h \
    GameComponent/node.h \
    GameComponent/map.h \
    GameComponent/squad.h \
    GameComponent/identitytoken.h \
    GameComponent/gamescene.h \
    GameComponent/GameInterface/button.h \
    GameComponent/GameInterface/progressbar.h \
    GameComponent/GameInterface/powerinterface.h \
    GameComponent/GameInterface/Powers/power.h \
    GameComponent/GameInterface/Powers/powerarmore.h \
    GameComponent/GameInterface/Powers/powerdestroy.h \
    GameComponent/GameInterface/Powers/powerinvincibility.h \
    GameComponent/GameInterface/Powers/powerteleportation.h \
    GameConnexion/client.h \
    GameConnexion/server.h \
    GameConnexion/gameserver.h \
    GameConnexion/gameclient.h \
    GameMenu/gamemenumanager.h \
    GameMenu/lobbymenu.h \
    GameMenu/welcomemenu.h \
    GameMenu/gamecontext.h \
    gamerlist.h \
    enumlibrary.h

SOURCES += \
    GameComponent/connexion.cpp \
    GameComponent/gamer.cpp \
    GameComponent/node.cpp \
    GameComponent/map.cpp \
    GameComponent/squad.cpp \
    GameComponent/identitytoken.cpp \
    GameComponent/gamescene.cpp \
    GameComponent/GameInterface/button.cpp \
    GameComponent/GameInterface/progressbar.cpp \
    GameComponent/GameInterface/powerinterface.cpp \
    GameComponent/GameInterface/Powers/power.cpp \
    GameComponent/GameInterface/Powers/powerarmore.cpp \
    GameComponent/GameInterface/Powers/powerdestroy.cpp \
    GameComponent/GameInterface/Powers/powerinvincibility.cpp \
    GameComponent/GameInterface/Powers/powerteleportation.cpp \
    GameConnexion/client.cpp \
    GameConnexion/server.cpp \
    GameConnexion/gameserver.cpp \
    GameConnexion/gameclient.cpp \
    GameMenu/gamemenumanager.cpp \
    GameMenu/lobbymenu.cpp \
    GameMenu/welcomemenu.cpp \
    GameMenu/gamecontext.cpp \
    gamerlist.cpp \
    main.cpp

OTHER_FILES += \
    Notes.txt

FORMS +=
