#ifndef PARSER_H
#define PARSER_H

#include <QObject>

namespace GameConnexion {
    class Parser;
}

class Parser : public QObject
{
    Q_OBJECT

public:
    Parser();

/*----------------------------------------------------*/
/*DECODE*/
/*----------------------------------------------------*/

public slots:
    void decode(QString s);

signals:
    void launchGame();
    void mapNameChange(QString mapName);
    void setGamerId(int id);
    void gamerLstUpdate();
    void mapCreation(QString s);
    void mapUpdate(QString s);

private:

/*----------------------------------------------------*/
/*ENCODE*/
/*----------------------------------------------------*/

public :
    enum ACTION
    {
        LAUNCHGAME,
        SETREADY,
        SETMAPNAME,
    };

    QString encode(ACTION a);
    QString encode(ACTION a, bool b);
    QString encode(ACTION a, int i);
    QString encode(ACTION a, QString s);

private:
};

#endif // PARSER_H
