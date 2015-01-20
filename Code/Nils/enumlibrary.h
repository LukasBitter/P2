#ifndef ENUMLIB_H
#define ENUMLIB_H

enum NETWORK_COMMANDE
{
    C_REQUEST_SLOT,
    C_GAMER_INFO,
    C_LAUNCH_GAME,
    C_REFUSE,
    C_NOT_READY,
    C_SET_READY,
    C_LOBBY_UPDATE,
    C_MAP_UPDATE,
    C_GAMER_ACTION,
    C_SET_NAME,
    C_ADD_MAP,
};

enum POWER_NAME
{
    P_DESTROY,
    P_INVINCIBILITY,
    P_TELEPORTATION,
    P_ARMORE,
};

enum GAMER_ACTION
{
    GA_SEND,
    GA_USEPOWER,
};

#endif // ENUMLIB_H
