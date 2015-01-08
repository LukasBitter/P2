#ifndef PARSERMAP_H
#define PARSERMAP_H

#include <QString>

class Map;

class ParserMap
{
public:
    ParserMap();
    virtual ~ParserMap();

    QString * parse(Map &m);
    void unParse(QString &s, Map &m);
};

#endif // PARSERMAP_H
