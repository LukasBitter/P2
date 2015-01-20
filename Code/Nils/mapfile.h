#ifndef MAPFILE_H
#define MAPFILE_H

#include <QStringList>
#include <QString>

class Gamer;

class MapFile
{
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    MapFile();
    ~MapFile();

    /*ASSESSEUR / MUTATEUR*/
    bool isValide();
    QString getCreationString();
    void setCreationString(QString s);
    QString getUpdateString();
    void setUpdateString(QString s);
    int getNumberOfSlot();
    void addSlot(QString gamerSlots);
    QString getSlot(int slotNumber, Gamer* g);

    /*LECTURE-ECRITURE*/
    void loadFromFile(QString file);
    void saveToFile(QString file);
private:
    /*ENTREE-SORTIE*/
    int version;
    QString creation;
    QString update;
    QStringList gamerSlots;
    bool valide;

    QStringList loadFileLine(QString file);
    void saveFileLine(QString file, QStringList line);
    void initialisation();
};

#endif // MAPFILE_H
