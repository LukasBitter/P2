#ifndef EDITVIEW_H
#define EDITVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include "connexion.h"
#include "enumlibrary.h"
#include "gamerlist.h"
#include "actionmanager.h"

class GameScene;
class PowerInterface;
class EditorInterface;

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
    ACTIONS a;
    Node *memory;

    /*METHODE PRIVE*/
    void setUpUI();
    QStringList normalizeNode();
};

#endif // EDITVIEW_H
