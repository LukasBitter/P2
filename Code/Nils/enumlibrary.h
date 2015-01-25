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
    I_CLIENT_PARAMETRED,
};

enum ACTIONS
{
    NO_ACTION,
    GA_SEND,
    GA_USEPOWER_DESTROY,
    GA_USEPOWER_INVINCIBILITY,
    GA_USEPOWER_TELEPORTATION,
    GA_USEPOWER_ARMORE,
    GA_GAME_FINISHED,
    GA_MANA_EMISSION,
    EA_ADD,
    EA_REMOVE,
    EA_CONNECT,
    EA_DISCONNECT,
};

//Creation de map
#define MAX_GAMER 4
#define VERSION_MAP 1
#define MAP_FILE "./maps"
#define MAP_EXTENSION "rtsmap"
#define MAP_EXTENSION_FILTER "*.rtsmap"

/*----------------------------------------------------*/
/*GAMEPLAY*/
/*----------------------------------------------------*/

//mana initiale
#define P_INITIAL_MANA 0

//cout des pouvoirs
#define P_TELEPORTATION_COST 40
#define P_ARMOR_COST 10
#define P_DESTROY_COST 80
#define P_INVINCIBILITY_COST 50

//temps recharge des pouvoirs
#define P_TELEPORTATION_CD 20
#define P_ARMOR_CD 5
#define P_DESTROY_CD 30
#define P_INVINCIBILITY_CD 30

//durée des pouvoirs
#define P_ARMOR_DURATION 5
#define P_INVINCIBILITY_DURATION 5

#endif // ENUMLIB_H
