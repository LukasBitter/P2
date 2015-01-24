#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include "connexion.h"
#include "enumlibrary.h"
#include "actionmanager.h"

class GameScene;
class Node;
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
public slots:
    void applyGamerAction(QString action);
private slots:
    void onPowerPressed(ACTIONS action);
    void onPowerStarting(ACTIONS a, Node *n1,Node *n2);
    void onPowerFinishing(ACTIONS a, Node *n1,Node *n2);
    void onDoAction(ACTIONS action, Node *n);
    void onDoAction(ACTIONS action, Node *n1, Node *n2);
private:
    /*INTERFACE*/
    PowerInterface *powerUi; ///< Interface utilisateur de gestion des pouvoirs

    /*ENTREE*/
    Gamer *owner; ///< Joueur actuellement au commande de la map

    /*OUTIL*/
    GameScene * scene; ///< Scene de jeu
    ActionManager am;
    double percentToSend; ///< Pourcentage du noeud à envoyer lors d'un envoi

    /*METHODE PRIVE*/
    void setUpUI();
    void sendSquad(Node *from, Node *to);
    void teleportSquad(Node *from, Node *to);
    void sendAction(ACTIONS a, int nodeFromId, int nodeToId, int param);
};

#endif // GAMEVIEW_H
