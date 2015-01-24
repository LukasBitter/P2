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
    explicit GameView(GamerList &gl, Gamer *g = 0, QWidget *parent=0);
    explicit GameView(QString create, GamerList &gl, Gamer *g=0, QWidget *parent=0);
    virtual ~GameView();
    /*DELEGUES*/
    QString getUpdateString();
    void updateFromString(QString s);
    QString getCreationString();

signals:
    void returnToMenu();

public slots:
    void advance();
private:
    /*INTERFACE*/
    PowerInterface *powerUi; ///< Interface utilisateur de gestion des pouvoirs

    /*ENTREE*/
    Gamer *owner; ///< Joueur actuellement au commande de la map

    /*OUTIL*/
    GameScene * scene; ///< Scene de jeu
    ActionManager actionManager;
    float percentToSend; ///< Pourcentage du noeud à envoyer lors d'un envoi

    /*METHODE PRIVE*/
    void setUpUI();


    /*----------------------------------------------------*/
    /*CAPTURE ACTIONS CLIENT*/
    /*----------------------------------------------------*/

public:
    /*SURCHARGE*/
    void keyPressEvent(QKeyEvent *e);
    void dropEvent(QDropEvent *event);

    /*ASSESSEUR / MUTATEUR*/
    void setPercentToSend(int percent);

    /*SIGNALS/SLOTS*/
signals:
    void gamerAction(QString action);
private slots:
    void selectionChange();
    void onDoAction(ACTIONS action);
    void onDoAction(ACTIONS action, Node *n);
    void onDoAction(ACTIONS action, Node *n1, Node *n2);
    void onPowerPressed( action);

    /*----------------------------------------------------*/
    /*RECEPTION ACTIONS SERVEUR*/
    /*----------------------------------------------------*/

public slots:
    void applyGamerAction(QString action);

private:
    /*METHODE PRIVE*/
    void sendSquad(Node *from, Node *to);
    void usePower(int nodeFromId, int nodeToId, POWER_NAME p);

 };

#endif // GAMEVIEW_H
