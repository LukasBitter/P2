#ifndef MAPFILE_H
#define MAPFILE_H

#include "global.h"

class Gamer;

/**
 * @class MapFile
 * @brief Permet de charger les données d'une map depuis
 * le disque ou de les écrire dans un fichier
 */
class MapFile
{
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    MapFile();

    /*ASSESSEUR / MUTATEUR*/
    bool isValide()const;
    QString getUpdateString()const;
    QString getCreationString() const;
    QString getSlot(int slotNumber, Gamer* g)const;
    int getVersion() const;
    int getNumberOfSlot()const;

    void setVersion(int v);
    void setUpdateString(QString s);
    void setCreationString(QString s);
    void addSlot(QString gamerSlots);

    /*LECTURE-ECRITURE*/
    void loadFromFile(const QString &file);
    void saveToFile(const QString &file)const;
private:
    /*ENTREE-SORTIE*/
    int version;  ///< Version de la map
    QString creation; ///< Chaine de création de la map
    QString update; ///< Chaine de première mise a jour de la map
    QStringList gamerSlots; ///< Liste des emplacement de spawn
    bool valide; ///< Indique si la map est charger correctement

    /*METHODE PRIVE*/
    QStringList loadFileLine(const QString &file)const;
    void saveFileLine(const QString &file, const QStringList &line)const;
    void initialisation();
};

#endif // MAPFILE_H
