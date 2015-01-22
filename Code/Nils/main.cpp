#include <QApplication>
#include "GameMenu/gamemenumanager.h"
#include "GameComponent/gameview.h"
#include "gamerlist.h"
#include "global.h"

#include "GameComponent/gamescene.h"
#include "GameComponent/node.h"

void createGame()
{
    GamerList l;
    GameScene s(l);
    Node &n1 = *new Node(100,100,20,50,l,0);
    Node &n2 = *new Node(400,100,20,50,l,0);
    Node &n3 = *new Node(200,200,20,50,l,0);
    Node &n4 = *new Node(500,100,20,50,l,0);
    s.addNode(n1);
    s.addNode(n2);
    s.addNode(n3);
    s.addNode(n4);
    s.addConnexion(n1,n2);
    s.addConnexion(n3,n2);
    s.addConnexion(n1,n3);
    s.addConnexion(n4,n3);
    s.advance();
    qDebug()<<s.getCreationString();
    qDebug()<<s.getUpdateString();
    qDebug()<<"_____________";
    GameScene s2(s.getCreationString(), l);
    QString txt = s.getUpdateString();
    s2.updateFromString(txt);
    qDebug()<<s2.getCreationString();
    qDebug()<<s2.getUpdateString();
    qDebug()<<"_____________";
    GameScene s3(s2.getCreationString(), l);
    QString txt1 = s2.getUpdateString();
    s3.updateFromString(txt1);
    qDebug()<<s3.getCreationString();
    qDebug()<<s3.getUpdateString();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    createGame();
//    return 0;


    GameMenuManager l;
    l.show();
    return a.exec();
}
