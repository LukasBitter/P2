#include "parser.h"
#include "enumLib.h"

Parser::Parser()
{
}

/*----------------------------------------------------*/
/*DECODE*/
/*----------------------------------------------------*/

void Parser::decode(QString s)
{

}

/*----------------------------------------------------*/
/*ENCODE*/
/*----------------------------------------------------*/

QString Parser::encode(Parser::ACTION a)
{
    switch(a)
    {
    case LAUNCHGAME:
        return QString("%1#").arg(C_LAUNCHGAME);

    default:
        return "";
    }
}

QString Parser::encode(Parser::ACTION a, bool b)
{
    switch(a)
    {
    case SETREADY:

        return "";

    default:
        return "";
    }
}

QString Parser::encode(Parser::ACTION a, int i)
{
    switch(a)
    {
    default:
        return "";
    }
}

QString Parser::encode(Parser::ACTION a, QString s)
{
    if(!s.contains("#"))
    {
        switch(a)
        {
        case SETMAPNAME:
                return QString("%1#%2").arg(C_SETREADY).arg(s);
        }
    }

    return "";
}
