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
/*PARSING*/
/*----------------------------------------------------*/

//public slots:
//    void parse(QString s);

//signals:
//    void launchGame();
//    void canRunGame(bool b);
//    void updateData();

//private:
//    void sousMethodeDeParsing1();
//    void sousMethodeDeParsing2();
//    void sousMethodeDeParsing3();
//    void sousMethodeDeParsing4();

///*----------------------------------------------------*/
///*UNPARSING*/
///*----------------------------------------------------*/

//public :
//    enum ACTION
//    {
//        LAUNCHGAME,
//        CANRUNGAME,
//        GAMEPLAY
//    };

//    QString unparse(ACTION a);
//    QString unparse(ACTION a, bool b);
//    QString unparse(ACTION a, int i);
//    QString unparse(ACTION a, QString s);

//private:
//    void sousMethodeDeUNParsing1();
//    void sousMethodeDeUNParsing2();
//    void sousMethodeDeUNParsing3();
//    void sousMethodeDeUNParsing4();
};

#endif // PARSER_H
