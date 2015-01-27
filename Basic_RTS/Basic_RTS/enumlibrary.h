#ifndef ENUMLIB_H
#define ENUMLIB_H

#include <QColor>

/*----------------------------------------------------*/
/*ENUMERATIONS*/
/*----------------------------------------------------*/

///Commandes envoyées entre le client de jeu et le serveur de jeu
enum NETWORK_COMMANDE
{
    C_REQUEST_SLOT,///< Client->Serveur : demande à participer à la partie
    C_GAMER_INFO,///< Client->Serveur : demande à participer à la partie
    C_LAUNCH_GAME,///< Client->Serveur : demande le lancemant de la partie
    C_TRANSIT_GAME,///< Serveur->Client : ordre de transition vers le jeu
    C_INFORMATION,///< Serveur->Client : Information d'ordre générale de type NETWORK_INFORMATION
    C_LOBBY_UPDATE,///< Serveur->Client : Mise a jour du salon de jeu
    C_MAP_UPDATE,///< Serveur->Client : Mise à jour du jeu client sur celui du serveur
    C_GAMER_ACTION,///< Serveur & Client : Message privés entre les GameView client et serveur
    C_ADD_MAP,///< Serveur->Client : Ajoute une map à la liste de choix de map
    C_UPDATE_CURRENT_GAMER,///< Client->Serveur : met à jour les données du joueur
    C_SEND_CHAT_MESSAGE,///< Client->Serveur : envois d'un message au autres joueurs
    C_RECIVE_CHAT_MESSAGE,///< Serveur->Client : réception d'un message des autres joueurs
    C_MAP_CHANGE,///< Serveur->Client : changement de la map de jeu
};

///Informations que le serveur envoi au client
enum NETWORK_INFORMATION
{
    I_OK,
    I_SAME_COLOR, ///< Erreur : Des joueurs ont la même couleur
    I_SAME_SLOT, ///< Erreur : Des joueurs ont le même slot de spawn
    I_GAME_STARTED, ///< Erreur : La partie est déjà commencée
    I_SLOT_NOT_SELECTED, ///< Erreur : Des joueurs n'ont pas sélectionné de spawn
    I_COLOR_NOT_SELECTED, ///< Erreur : Des joueurs n'ont pas sélectionné de couleur
    I_MAP_INVALID, ///< Erreur : Des joueurs n'ont pas sélectionné de spawn
    I_MAP_NOT_BIG_ENOUGH,///< Erreur : La map demandée par le client est invalide
    I_NOT_READY,///< Erreur : Des joueurs ne sont pas prêt
    I_CLIENT_PARAMETRED,///< Information : Le client parametré est ajouté au serveur
    I_LOBBY_FULL,///< Information : Le salon est plein
};

///Actions échangées entre les jeux coté client et serveur (GA = action en jeu ; EA = action editeur)
enum ACTIONS
{
    NO_ACTION, ///< Pas d'action
    GA_SEND, ///< Envoi d'unité via les connexions
    GA_USEPOWER_DESTROY, ///< Utilisation du pouvoir "destruction"
    GA_USEPOWER_INVINCIBILITY, ///< Utilisation du pouvoir "invincibilité"
    GA_USEPOWER_TELEPORTATION, ///< Utilisation du pouvoir "teleportation"
    GA_USEPOWER_ARMORE, ///< Utilisation du pouvoir "armure"
    GA_GAME_FINISHED, ///< Signal de fin de jeu
    GA_MANA_BURN, ///< Destruction de ressource à cause d'un gain de mana
    EA_ADD, ///< Ajout d'un noeud à la map
    EA_REMOVE, ///< Suppression d'un noeud de la map
    EA_CONNECT, ///< Connecte deux noeuds
    EA_DISCONNECT, ///< Déconnecte deux noeuds
};

///Image des boutons dans le jeu
enum BUTTON_TYPE
{
    ARMOR,          /// Bouclie
    INVINCIBILITY,  /// Invincibilité
    TELEPORTATION,  /// Téléportation
    DESTRUCTION,    /// Destruction
    INCRASE,        /// Augmente le taux d'envoi
    DICRASE,        /// Diminue le taux d'envoi
};

/*----------------------------------------------------*/
/*GENERAL*/
/*----------------------------------------------------*/

//fréquence de la boucle de rafraichissement en milliseconde
//de l'interface des pouvoir en local chez le client
#define POWER_TIC 100
//fréquence de la boucle de rafraichissement en milliseconde
//du jeu sur le serveur
#define GAME_TIC 75
//fréquence de la boucle de rafraichissement en milliseconde
//de la barre de statistique sur les ressource
#define RESSOURCES_BAR_TIC 500
//port de connexion
#define PORT 8000
//maximum de joueur dans le salon
#define MAX_GAMER 4
#define PLAYER_COLOR {Qt::darkRed, Qt::darkGreen, Qt::darkYellow, Qt::darkCyan}
//Numéro de version des map supportées
#define VERSION_MAP 1
//Enregistrement et lecture des maps
#define MAP_FILE "./maps"
#define MAP_EXTENSION "rtsmap"
#define MAP_EXTENSION_FILTER "*.rtsmap"

/*----------------------------------------------------*/
/*GRAPHISME*/
/*----------------------------------------------------*/

#define VACANT_COLOR Qt::white
#define BASE_NODE_COLOR Qt::darkBlue

/*----------------------------------------------------*/
/*GAMEPLAY*/
/*----------------------------------------------------*/

//mana initiale
#define P_INITIAL_MANA 0
#define P_MAX_MANA 200

//cout des pouvoirs
#define P_TELEPORTATION_COST 40
#define P_ARMOR_COST 10
#define P_DESTROY_COST 80
#define P_INVINCIBILITY_COST 50

//temps recharge des pouvoirs en tic de POWER_TIC
#define P_TELEPORTATION_CD 200
#define P_ARMOR_CD 50
#define P_DESTROY_CD 300
#define P_INVINCIBILITY_CD 300

//durée des pouvoirs
#define P_ARMOR_DURATION 50
#define P_INVINCIBILITY_DURATION 50

#endif // ENUMLIB_H
