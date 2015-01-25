#include "mapfile.h"
#include "gamer.h"
#include "GameComponent/Logic/node.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

MapFile::MapFile()
{
    initialisation();
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
    qDebug()<<"MapFile : enter 'getCreationString'";

    if(valide)
    {
        return creation;
    }

    return "";
}

QString MapFile::getUpdateString() const
{
    qDebug()<<"MapFile : enter 'getUpdateString'";

    if(valide)
    {
        return update;
    }

    return "";
}

int MapFile::getNumberOfSlot() const
{
    qDebug()<<"MapFile : enter 'getNumberOfSlot'";

    if(valide)
    {
        return gamerSlots.size();
    }

    return 0;
}

void MapFile::addSlot(QString s)
{
    qDebug()<<"MapFile : enter 'addSlot'";

    gamerSlots.append(s);
}

QString MapFile::getSlot(int slotNumber, Gamer *g) const
{
    qDebug()<<"MapFile : enter 'getSlot'";

    int gamerId = 0;

    if(g != 0)
    {
        gamerId = g->getId();
    }

    if(valide && slotNumber < gamerSlots.size()  && slotNumber >= 0)
    {

        qDebug()<<"MapFile : in 'getSlot' value returned : "<<QString(gamerSlots.value(slotNumber)).arg(gamerId);

        return QString(gamerSlots.value(slotNumber)).arg(gamerId);
    }

    return "";
}

int MapFile::getVersion() const
{
    qDebug()<<"MapFile : enter 'getVersion'";

    return version;
}

void MapFile::setVersion(int v)
{
    qDebug()<<"MapFile : enter 'setVersion'";

    version = v;
}

void MapFile::setUpdateString(QString s)
{
    update = s;
}

void MapFile::setCreationString(QString s)
{
    creation = s;
}

/*----------------------------------------------------*/
/*LECTURE-ECRITURE*/
/*----------------------------------------------------*/

void MapFile::loadFromFile(const QString &file)
{
    qDebug()<<"MapFile : enter 'loadFromFile'";

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

void MapFile::saveToFile(const QString &file) const
{
    qDebug()<<"MapFile : enter 'saveToFile'";

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

QStringList MapFile::loadFileLine(const QString &file) const
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

void MapFile::saveFileLine(const QString &file, const QStringList &line)const
{
    qDebug()<<"MapFile : enter 'saveFileLine'";

    QFile f(file);

    if(f.exists())
    {
        qWarning()<<"MapFile : the file already exist";
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
    valide = false;
    gamerSlots.clear();
}
