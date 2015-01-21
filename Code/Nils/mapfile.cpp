#include "mapfile.h"
#include "gamer.h"
#include "GameComponent/node.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

MapFile::MapFile()
{
    initialisation();
}

MapFile::~MapFile()
{

}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

bool MapFile::isValide() const
{
    return valide;
}

QString MapFile::getCreationString() const
{
    if(valide)
    {
        return creation;
    }
    return "";
}

QString MapFile::getUpdateString() const
{
    if(valide)
    {
        return update;
    }
    return "";
}

int MapFile::getNumberOfSlot() const
{
    if(valide)
    {
        return gamerSlots.size();
    }
    return 0;
}

void MapFile::addSlot(QString s)
{
    gamerSlots.append(s);
}

QString MapFile::getSlot(int slotNumber, Gamer *g) const
{
    int gamerId = 0;
    if(g != 0)
    {
        gamerId = g->getId();
    }

    if(valide && slotNumber < gamerSlots.size()  && slotNumber >= 0)
    {
        qDebug()<<gamerSlots.size();
        qDebug()<<gamerSlots.value(slotNumber);
        return QString(gamerSlots.value(slotNumber)).arg(gamerId);
    }
    return "";
}

int MapFile::getVersion() const
{
    return version;
}

void MapFile::setVersion(int v)
{
    version = v;
}

/*----------------------------------------------------*/
/*LECTURE-ECRITURE*/
/*----------------------------------------------------*/

void MapFile::loadFromFile(QString file)
{
    initialisation();
    bool versionOk = false;
    bool nbGamerOk = false;
    int nbGamer = 0;
    QStringList lstFile = loadFileLine(file);

    if(lstFile.size() >= 6)
    {
        version = lstFile.value(0).toInt(&versionOk);
        creation = lstFile.value(1);
        update = lstFile.value(2);
        nbGamer = lstFile.value(3).toInt(&nbGamerOk);

        for(int i = 0; i < nbGamer; ++i)
        {
            QString tmp = lstFile.value(i+4);
            if(!tmp.isEmpty())
            {
                gamerSlots<<tmp;
            }
        }

        if(versionOk && nbGamerOk && gamerSlots.size() == nbGamer)
        {
            valide = true;
        }
    }
}

void MapFile::saveToFile(QString file)
{
    QStringList line;

    line.append(QString("%1").arg(version));
    line.append(creation);
    line.append(update);
    line.append(QString("%1").arg(gamerSlots.size()));
    line.append(gamerSlots);

    saveFileLine(file, line);
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

QStringList MapFile::loadFileLine(QString file)
{
    qDebug()<<"MapFile : enter 'loadFileLine'";
    QStringList lstFile;
    QFile f(file);

    if(!f.exists())
    {
        qWarning()<<"MapFile : the file dosen't exist";
    }
    else
    {
        if (f.open(QIODevice::ReadOnly))
        {
            QTextStream in(&f);
            while (!in.atEnd())
            {
                lstFile<<in.readLine();
            }
            f.close();
        }
        else
        {
            qWarning()<<"MapFile : the file can't be read";
        }
    }

    return lstFile;
}

void MapFile::saveFileLine(QString file, QStringList line)
{
    qDebug()<<"MapFile : enter 'saveFileLine'";
    QFile f(file);

    if(!f.exists())
    {
        qWarning()<<"MapFile : the file dosen't exist";
    }
    else
    {
        if (f.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&f);
            foreach(QString s , line)
            {
                out<<s<<"\n";
            }
            f.close();
        }
        else
        {
            qWarning()<<"MapFile : the file can't be write";
        }
    }
}

void MapFile::initialisation()
{
    version = 0;
    creation = "";
    update = "";
    gamerSlots.clear();
    valide = false;
}
