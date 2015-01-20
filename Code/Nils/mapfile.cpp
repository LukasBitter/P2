#include "mapfile.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

MapFile::MapFile()
{
    initialisation();
}

MapFile::~MapFile()
{

}

bool MapFile::isValide()
{
    return valide;
}

QString MapFile::getCreationString()
{
    if(valide)
    {
        return creation;
    }
    return "";
}

QString MapFile::getUpdateString()
{
    if(valide)
    {
        return update;
    }
    return "";
}

int MapFile::getNumberOfSlot()
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

QString MapFile::getSlot(int slotNumber, Gamer *g)
{
    if(valide)
    {
        return gamerSlots.value(slotNumber);
    }
    return "";
}

void MapFile::loadFromFile(QString file)
{
    initialisation();
    bool versionOk = false;
    bool nbGamerOk = false;
    QStringList lstFile = loadFileLine(file);

    if(lstFile.size() >= 6)
    {
        int nbGamer = 0;
        version = lstFile.value(0).toInt(&versionOk);
        creation = lstFile.value(1);
        update = lstFile.value(2);
        nbGamer = lstFile.value(3).toInt(&nbGamerOk);

        for(int i = 0; i < nbGamer; ++i)
        {
            gamerSlots<<lstFile.value(i+4);
        }

        if(versionOk && nbGamerOk)
        {
            valide = true;
        }
    }
}

void MapFile::saveToFile(QString file)
{

}

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

void MapFile::initialisation()
{
    version = 0;
    creation = "";
    update = "";
    gamerSlots.clear();
    valide = false;
}
