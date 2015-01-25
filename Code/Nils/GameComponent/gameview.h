#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include "connexion.h"
#include "enumlibrary.h"
#include "actionmanager.h"

class GameScene;
class NodeCombat;
class QDropEvent;
class PowerInterface;

namespace GameComponent
{
class GameView;
}

/**
 * @class Map
 * @brief Vue du jeu
 */
class GameView: public QGraphicsView
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    void initialize();
    explicit GameView(GamerList &gl, Gamer *g = 0, QWidget *parent=0);
    explicit GameView(QString create, GamerList &gl, Gamer *g=0, QWidget *parent=0);
    virtual ~GameView();

    /*SURCHARGE*/
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void dropEvent(QDropEvent *event);

    /*ASSESSEUR / MUTATEUR*/
    void setPercentToSend(int percent);
    static bool isContainsPrivateChar(QString &s);

    /*DELEGUES*/
    QString getUpdateString();
    void updateFromString(QString s);
    QString getCreationString();

public slots:
    void advance();

    /*SIGNALS/SLOTS*/
signals:
    void gamerAction(QString action);
    void returnToMenu();
    void gameFinish(bool victory);
public slots:
    void applyGamerAction(QString action);
private slots:
    void onPowerPressed(ACTIONS action);
    void onPowerStarting(ACTIONS a, NodeCombat *n1,NodeCombat *n2);
    void onPowerFinishing(ACTIONS a, NodeCombat *n1,NodeCombat *n2);
    void onDoAction(ACTIONS action, NodeCombat *n);
    void onDoAction(ACTIONS action, NodeCombat *n1, NodeCombat *n2);
private:
    /*INTERFACE*/
    PowerInterface *powerUi; ///< Interface utilisateur de gestion des pouvoirs

    /*ENTREE*/
    Gamer *owner; ///< Joueur actuellement au commande de la map

    /*OUTIL*/
    GameScene * scene; ///< Scene de jeu
    ActionManager am;
    double percentToSend; ///< Pourcentage du noeud à envoyer lors d'un envoi
    bool gameFinished;

    /*METHODE PRIVE*/
    void setUpUI();
    void sendSquad(NodeCombat *from, NodeCombat *to);
    void teleportSquad(NodeCombat *from, NodeCombat *to);
    void sendAction(ACTIONS a, int nodeFromId, int nodeToId, int param);
};

#endif // GAMEVIEW_H
