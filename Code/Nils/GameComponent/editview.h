#ifndef EDITVIEW_H
#define EDITVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include "connexion.h"
#include "enumlibrary.h"
#include "gamerlist.h"
#include "actionmanager.h"

class GameScene;
class EditorInterface;
class Node;
class Gamer;

namespace GameComponent
{
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
    void mousePressEvent(QMouseEvent *e);

    /*ASSESSEUR / MUTATEUR*/
    void clearMap();

    /*LECTURE-ECRITURE*/
    void loadMapName(QString s);
    void saveMapName(QString s);

    /*SIGNALS/SLOTS*/
signals:
    void returnToMenu();
private slots:
    void onBtActionPressed(ACTIONS a);
    void onBtSaveToFilePressed();
    void onBtLoadFromFilePressed();
    void onBtReturnPressed();

private:
    /*INTERFACE*/
    EditorInterface *editorUi;

    /*OUTIL*/
    GameScene * scene; ///< Scene de jeu
    GamerList lstGamer;
    Gamer *spawnGamer;
    ACTIONS a;
    Node *memory;

    /*METHODE PRIVE*/
    void setUpUI();
};

#endif // EDITVIEW_H
