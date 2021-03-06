#ifndef EDITVIEW_H
#define EDITVIEW_H

#include "global.h"
#include "GameComponent/Logic/connexion.h"
#include "enumlibrary.h"
#include "gamerlist.h"

class GameScene;
class EditorInterface;
class Gamer;
class NodeConnectable;

namespace GameComponent
{
    class EditView;
}

/**
 * @class EditView
 * @brief Editeur du map
 * Permet de créer des maps personnalisées
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
    void clearMap();

private:
    /*INTERFACE*/
    EditorInterface *editorUi; ///< Palette d'édition

    /*OUTIL*/
    GameScene * scene; ///< Scene de jeu
    GamerList lstGamer; ///< Liste des joueurs factice
    Gamer *spawnGamer; ///< Joueur marquant le spawn
    ACTIONS a; ///< Action en cours
    NodeConnectable *memory; ///< Mémoire du noeud sélectionné précédement

    /*METHODE PRIVE*/
    void setUpUI();
    void newScene();
};

#endif // EDITVIEW_H
