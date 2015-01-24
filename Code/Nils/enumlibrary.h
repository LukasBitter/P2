#ifndef ENUMLIB_H
#define ENUMLIB_H

enum NETWORK_COMMANDE
{
    C_REQUEST_SLOT,
    C_GAMER_INFO,
    C_LAUNCH_GAME,
    C_INFORMATION,
    C_LOBBY_UPDATE,
    C_MAP_UPDATE,
    C_GAMER_ACTION,
    C_ADD_MAP,
    C_UPDATE_CURRENT_GAMER,
};

enum POWER_NAME
{
    P_NONE,
    P_DESTROY,
    P_INVINCIBILITY,
    P_TELEPORTATION,
    P_ARMORE,
};

enum ACTIONS
{
    NO_ACTION,
    GA_SEND,
    GA_USEPOWER_DESTROY,
    GA_USEPOWER_INVINCIBILITY,
    GA_USEPOWER_TELEPORTATION,
    GA_USEPOWER_ARMORE,
    EA_ADD,
    EA_REMOVE,
    EA_CONNECT,
    EA_DISCONNECT,
};

enum NETWORK_INFORMATION
{
    I_OK,
    I_SAME_COLOR,
    I_SAME_SLOT,
    I_GAME_STARTED,
    I_SLOT_NOT_SELECTED,
    I_COLOR_NOT_SELECTED,
    I_MAP_INVALID,
    I_MAP_NOT_BIG_ENOUGH,
    I_NOT_READY,
};

#define MAX_GAMER 4
#define VERSION_MAP 1
#define MAP_FILE "./maps"
#define MAP_EXTENSION "rtsmap"
#define MAP_EXTENSION_FILTER "*.rtsmap"

#endif // ENUMLIB_H
