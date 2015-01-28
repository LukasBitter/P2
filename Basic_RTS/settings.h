#ifndef SETTINGS_H
#define SETTINGS_H

#include "global.h"

/*----------------------------------------------------*/
/*LECTURE-ECRITURE*/
/*----------------------------------------------------*/

/**
 * @brief losdSettingFromFile Charge les parametre de configurations
 * depuis un fichier
 */
void loadSettingFromFile();
/**
 * @brief createDefaultSettingFile Creation d'un fichier de configuration
 * par defaut
 */
void createDefaultSettingFile();

/*----------------------------------------------------*/
/*MISE A JOUR*/
/*----------------------------------------------------*/

QString getUpdateSettingString();
void updateSettingFromString(const QString &s);


/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

/**
 * @brief serverUpdateLoop Retourne la fréquence
 * de mise à jour du serveur de jeu
 * @return fréquence en milliseconde
 *
 * Influence la vitesse du jeu
 */
int serverUpdateLoop();

/**
 * @brief clientUpdateLoop Retourne la fréquence
 * de mise à jour de l'interface coté client
 * @return fréquence en milliseconde
 *
 * Influence la vitesse de rechargement des pouvoirs
 * et autres compétence propre au UI du client
 */
int clientUpdateLoop();

/**
 * @brief connexionPort Retourne le port de connexionPort
 * utiliser par les client et le serveur
 */
int connexionPort();

/*----------------------------------------------------*/
/*GAMEPLAY*/
/*----------------------------------------------------*/

/**
 * @brief maxGamer Retourne le nombre maximum de joueur
 */
int maxGamer();

/**
 * @brief getGamerColorList Retourne une liste de la couleur
 * de chaque joueur
 */
QList<QColor> getGamerColorList();

/**
 * @brief initialMana Retourne la quantité de mana initiale
 */
int initialMana();

/**
 * @brief maxMana Retourne la quantité de mana maximum
 */
int maxMana();

/**
 * @brief armorCost Retourne le cout du pouvoir armure
 */
int armorCost();

/**
 * @brief teleportationCost Retourne le cout du pouvoir teleportation
 */
int teleportationCost();

/**
 * @brief destroyCost Retourne le cout du pouvoir destruction
 */
int destroyCost();

/**
 * @brief invincibilityCost Retourne le cout du pouvoir invincibilité
 */
int invincibilityCost();

/**
 * @brief armorDuration Retourne la durée du pouvoir armure
 */
int armorDuration();

/**
 * @brief armorDuration Retourne la durée du pouvoir invincibilité
 */
int invincibilityDuration();

/**
 * @brief armorCD Retourne le temps de recharge du pouvoir armure
 */
int armorCD();

/**
 * @brief teleportationCD Retourne le temps de recharge du pouvoir teleportation
 */
int teleportationCD();

/**
 * @brief destroyCD Retourne le temps de recharge du pouvoir destruction
 */
int destroyCD();

/**
 * @brief invincibilityCD Retourne le temps de recharge du pouvoir invincibilité
 */
int invincibilityCD();

/**
 * @brief debugNoWin Desactive la condition de victoire (pour du debug)
 */
bool debugNoWin();


#endif // SETTINGS_H
