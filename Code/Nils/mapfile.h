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
    bool isValide()const;
    QString getCreationString()const;
    void setCreationString(QString s);
    QString getUpdateString()const;
    void setUpdateString(QString s);
    int getNumberOfSlot()const;
    void addSlot(QString gamerSlots);
    QString getSlot(int slotNumber, Gamer* g)const;
    int getVersion() const;
    void setVersion(int v);

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

    /*METHODE PRIVE*/
    QStringList loadFileLine(QString file);
    void saveFileLine(QString file, QStringList line);
    void initialisation();
};

#endif // MAPFILE_H
