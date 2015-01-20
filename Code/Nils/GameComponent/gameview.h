#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include "connexion.h"
#include "enumlibrary.h"

class GameScene;
class Node;
class Connexion;
class QDropEvent;
class PowerInterface;

namespace GameComponent {
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
    explicit GameView(GamerList &gl, const Gamer *g = 0, QWidget *parent=0);
    explicit GameView(QString create, GamerList &gl, const Gamer *g=0, QWidget *parent=0);
    virtual ~GameView();

    /*SURCHARGE*/
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void dropEvent(QDropEvent *event);

    /*MISE A JOUR*/
    QString getUpdateString();
    void updateFromString(QString &s);
    QString getCreationString();

    /*SIGNALS/SLOTS*/
    void setPercentToSend(int percent);
signals:
    void gamerAction(QString action);
public slots:
    void advance();
    void applyGamerAction(QString action);
private slots:
    void selectionChange();

private:
    /*INTERFACE*/
    PowerInterface *ui; ///< Interface utilisateur de gestion des pouvoirs
    const Gamer *owner; ///< Joueur actuellement au commande de la map
    Node *currentSelection;
    Node *lastSelection;

    /*OUTIL*/
    GameScene * scene; ///< Scene de jeu
    float percentToSend; ///< Pourcentage du noeud à envoyer lors d'un envoi

    /*METHODE PRIVE*/
    void sendSquad(Node *from, Node *to);
    void usePower(int nodeFromId, int nodeToId, POWER_NAME p);
    void setUpUI();
 };

#endif // GAMEVIEW_H
