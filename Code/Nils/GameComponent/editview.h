#ifndef EDITVIEW_H
#define EDITVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include "connexion.h"
#include "enumlibrary.h"
#include "gamerlist.h"

class GameScene;
class Node;
class Connexion;
class QDropEvent;
class PowerInterface;

namespace GameComponent {
class EditView;
}

/**
 * @class Map
 * @brief Editeur du jeu
 */
class EditView: public QGraphicsView
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit EditView(QWidget *parent=0);
    virtual ~EditView();

    /*SURCHARGE*/
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void dropEvent(QDropEvent *event);

    /*LECTURE-ECRITURE*/
    void loadMapName(QString s);
    void saveMapName(QString s);

private slots:
    void selectionChange();

private:
    /*OUTIL*/
    GameScene * scene; ///< Scene de jeu
    GamerList lstGamer;
    EDITOR_ACTION action;
    Node *currentSelection;
    Node *lastSelection;

    /*METHODE PRIVE*/
    void setUpUI();
    void clearMap();
};

#endif // EDITVIEW_H
