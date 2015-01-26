#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "global.h"
#include "enumlibrary.h"
#include "actionmanager.h"

class GameScene;
class GamerList;
class NodeCombat;
class QDropEvent;
class PowerInterface;
class Gamer;

namespace GameComponent
{
    class GameView;
}

/**
 * @class GameView
 * @brief Affichage du jeu
 * Affiche la partie en cour et permet récupère les actions du joueur
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
    void onPowerStarting(ACTIONS a, Node *n1, Node *n2);
    void onPowerFinishing(ACTIONS a, Node *n1, Node *n2);
    void onDoAction(ACTIONS action, Node *n);
    void onDoAction(ACTIONS action, Node *n1, Node *n2);
private:
    /*INTERFACE*/
    PowerInterface *powerUi; ///< Palette de gestion des pouvoirs

    /*ENTREE*/
    Gamer *owner; ///< Joueur actuellement au commande de la map

    /*OUTIL*/
    GameScene * scene; ///< Scene de jeu
    ActionManager am; ///< Gestionnaire des actions du joueur
    double percentToSend; ///< Pourcentage du noeud à envoyer lors d'un envoi
    bool gameFinished; ///< Indique si le jeu est fini

    /*METHODE PRIVE*/
    void setUpUI();

    /*ENVOIS*/
    void sendSquad(Node *from, Node *to);
    void sendAction(ACTIONS a, int nodeFromId, int nodeToId, int param);

    /*RECEPTION*/
    void receive_GA_SEND(int gamerId, Node *nodeFrom, Node *nodeTo, int param);
    void receive_GA_USEPOWER_DESTROY(int gamerId, Node *nodeFrom, Node *nodeTo, int param);
    void receive_GA_USEPOWER_INVINCIBILITY(int gamerId, Node *nodeFrom, Node *nodeTo, int param);
    void receive_GA_USEPOWER_ARMORE(int gamerId, Node *nodeFrom, Node *nodeTo, int param);
    void receive_GA_USEPOWER_TELEPORTATION(int gamerId, Node *nodeFrom, Node *nodeTo, int param);
    void receive_GA_GAME_FINISHED(int gamerId, Node *nodeFrom, Node *nodeTo, int param);
    void receive_GA_MANA_BURN(int gamerId, Node *nodeFrom, Node *nodeTo, int param);
};

#endif // GAMEVIEW_H
