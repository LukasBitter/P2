#include "settings.h"
#include "enumlibrary.h"

int _serverUpdateLoop;
int _clientUpdateLoop;
int _connexionPort;
QList<QColor> _lstGamerColorList;
bool _debugNoWin;

//Parametre depuis le serveur
int _initialMana;
int _maxMana;
int _armorCost;
int _teleportationCost;
int _destroyCost;
int _invincibilityCost;
int _armorDuration;
int _invincibilityDuration;
int _teleportationPercent;
int _destructionPercent;
int _armorCD;
int _teleportationCD;
int _destroyCD;
int _invincibilityCD;

/*----------------------------------------------------*/
/*LECTURE-ECRITURE*/
/*----------------------------------------------------*/

void loadSettingFromFile()
{
    qDebug()<<"Setting : enter in 'loadSettingFromFile'";

    QSettings ini(CONFIG_FILE, QSettings::IniFormat);
    _serverUpdateLoop = ini.value("serverUpdateLoop","100").toInt();
    _clientUpdateLoop = ini.value("clientUpdateLoop","100").toInt();
    _connexionPort = ini.value("connexionPort","8000").toInt();

    int cptGamer = 0;
    QString color = ini.value(QString("Gamer_%1").arg(cptGamer),"").toString();
    while(!color.isEmpty())
    {
        _lstGamerColorList.append(QColor(color));
        ++cptGamer;
        color = ini.value(QString("Gamer_%1").arg(cptGamer),"").toString();
    }

    _initialMana = ini.value("initialMana","0").toInt();
    _maxMana = ini.value("connexionPort","100").toInt();
    _armorCost = ini.value("armorCost","10").toInt();
    _teleportationCost = ini.value("teleportationCost","40").toInt();
    _destroyCost = ini.value("destroyCost","80").toInt();
    _invincibilityCost = ini.value("invincibilityCost","50").toInt();

    _armorDuration = ini.value("armorDuration","50").toInt();
    _invincibilityDuration = ini.value("invincibilityDuration","50").toInt();
    _teleportationPercent = ini.value("teleportationPercent","50").toInt();
    _destructionPercent = ini.value("destructionPercent","100").toInt();

    _armorCD = ini.value("armorCD","50").toInt();
    _teleportationCD = ini.value("teleportationCD","200").toInt();
    _destroyCD = ini.value("destroyCD","300").toInt();
    _invincibilityCD = ini.value("invincibilityCD","300").toInt();
    _debugNoWin = ini.value("debugNoWin","0").toBool();

}

void createDefaultSettingFile()
{
    qDebug()<<"Setting : enter in 'createDefaultSettingFile'";

    QSettings ini(CONFIG_FILE, QSettings::IniFormat);
    ini.setValue("serverUpdateLoop", 100);
    ini.setValue("clientUpdateLoop", 100);
    ini.setValue("connexionPort", 8000);
    ini.setValue("initialMana", 0);
    ini.setValue("maxMana", 100);
    ini.setValue("armorCost", 10);
    ini.setValue("teleportationCost", 40);
    ini.setValue("destroyCost", 80);
    ini.setValue("invincibilityCost", 50);
    ini.setValue("armorDuration", 50);
    ini.setValue("invincibilityDuration", 50);
    ini.setValue("teleportationPercent", 50);
    ini.setValue("destructionPercent", 100);
    ini.setValue("armorCD", 50);
    ini.setValue("teleportationCD", 200);
    ini.setValue("destroyCD", 300);
    ini.setValue("invincibilityCD", 300);
    ini.setValue("Gamer_0", QColor(Qt::darkRed).name());
    ini.setValue("Gamer_1", QColor(Qt::darkGreen).name());
    ini.setValue("Gamer_2", QColor(Qt::darkYellow).name());
    ini.setValue("Gamer_3", QColor(Qt::darkMagenta).name());
}

/*----------------------------------------------------*/
/*MISE A JOUR*/
/*----------------------------------------------------*/

QString getUpdateSettingString()
{
    return QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14").
            arg(_initialMana).arg(_maxMana).arg(_armorCost).
            arg(_teleportationCost).arg(_destroyCost).
            arg(_invincibilityCost).arg(_armorDuration).arg(_invincibilityDuration).
            arg(_teleportationPercent).arg(_destructionPercent).arg(_armorCD).
            arg(_teleportationCD).arg(_destroyCD).arg(_invincibilityCD);
}


void updateSettingFromString(const QString &s)
{
    QStringList nodeStr = s.split(",");
    if(nodeStr.size() == 14)
    {
        _initialMana = nodeStr.first().toInt();
        nodeStr.pop_front();
        _maxMana = nodeStr.first().toInt();
        nodeStr.pop_front();
        _armorCost = nodeStr.first().toInt();
        nodeStr.pop_front();
        _teleportationCost = nodeStr.first().toInt();
        nodeStr.pop_front();
        _destroyCost = nodeStr.first().toInt();
        nodeStr.pop_front();
        _invincibilityCost = nodeStr.first().toInt();
        nodeStr.pop_front();
        _armorDuration = nodeStr.first().toInt();
        nodeStr.pop_front();
        _invincibilityDuration = nodeStr.first().toInt();
        nodeStr.pop_front();
        _teleportationPercent = nodeStr.first().toInt();
        nodeStr.pop_front();
        _destructionPercent = nodeStr.first().toInt();
        nodeStr.pop_front();
        _armorCD = nodeStr.first().toInt();
        nodeStr.pop_front();
        _teleportationCD = nodeStr.first().toInt();
        nodeStr.pop_front();
        _destroyCD = nodeStr.first().toInt();
        nodeStr.pop_front();
        _invincibilityCD = nodeStr.first().toInt();
        nodeStr.pop_front();
    }
    else
    {
        qCritical()<<"Setting : unexpected case in 'updateFromString'";
    }
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

int serverUpdateLoop()
{
    return _serverUpdateLoop;
}

int clientUpdateLoop()
{
    return _clientUpdateLoop;
}


int connexionPort()
{
    return _connexionPort;
}


QList<QColor> getGamerColorList()
{
    return _lstGamerColorList;
}


int maxGamer()
{
    return _lstGamerColorList.size();
}


int maxMana()
{
    return _maxMana;
}


int initialMana()
{
    return _initialMana;
}


int armorCost()
{
    return _armorCost;
}


int teleportationCost()
{
    return _teleportationCost;
}


int destroyCost()
{
    return _destroyCost;
}


int invincibilityCost()
{
    return _invincibilityCost;
}


int armorDuration()
{
    return _armorDuration;
}


int invincibilityDuration()
{
    return _invincibilityDuration;
}


int armorCD()
{
    return _armorCD;
}


int teleportationCD()
{
    return _teleportationCD;
}


int destroyCD()
{
    return _destroyCD;
}


int invincibilityCD()
{
    return _invincibilityCD;
}



bool debugNoWin()
{
    return _debugNoWin;
}
