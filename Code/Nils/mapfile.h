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

    /*ASSESSEUR / MUTATEUR*/
    bool isValide()const;
    QString getUpdateString()const;
    QString getCreationString() const;
    QString getSlot(int slotNumber, Gamer* g)const;
    int getVersion() const;
    int getNumberOfSlot()const;

    void setVersion(int v);
    void setUpdateString(QString s);
    void addSlot(QString gamerSlots);

    /*LECTURE-ECRITURE*/
    void loadFromFile(const QString &file);
    void saveToFile(const QString &file)const;
private:
    /*ENTREE-SORTIE*/
    int version;
    QString creation;
    QString update;
    QStringList gamerSlots;
    bool valide;

    /*METHODE PRIVE*/
    QStringList loadFileLine(const QString &file)const;
    void saveFileLine(const QString &file, const QStringList &line)const;
    void initialisation();
};

#endif // MAPFILE_H
