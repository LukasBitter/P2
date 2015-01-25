#ifndef LOBBYMENU_H
#define LOBBYMENU_H

#include "global.h"
#include "enumlibrary.h"

class GameServer;
class GameClient;
class GameView;

namespace GameMenu
{
    class LobbyMenu;
}

/**
 * @class LobbyMenu
 * @brief Menu du salon de jeu (avant la partie)
 */
class LobbyMenu : public QWidget
{
    Q_OBJECT
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    LobbyMenu(QWidget *parent = 0);

    /*SIGNALS/SLOTS*/
signals:
    void returnToMenu();
    void play(GameView *gc);
    void mapSelectionUpdate();

public slots:
    void enableClientUI();
    void enableServerUI();

private slots:
    void updateUI();
    void launchGame();
    void showError(QAbstractSocket::SocketError err);
    void showMessage(NETWORK_INFORMATION err);
    void onBtReturnPressed();
    void onBtConnectPressed();
    void onBtStartPressed();
    void onBtChangeNamePressed();
    void onBtReadyPressed();
    void onSuccessfulConnexion();
    void onAddMap(QString s);
    void onCbbColorChanged(int i);
    void onCbbSlotChanged(int i);

private:
    /*INTERFACE*/
    QLineEdit *txtAdressIP;
    QLabel *txtName;
    QPushButton *btChangeName;
    QPushButton *btConnect;
    QTableWidget *tblStatus;
    QComboBox *cbbMap;
    QCheckBox *cbtReady;
    QComboBox *cbbSlot;
    QComboBox *cbbColor;
    QPushButton *btStart;
    QPushButton *btReturn;
    QLabel *txtConnected;

    /*OUTIL*/
    bool host; ///< Indique si le joueur est l'host
    GameServer *server; ///< Serveur de jeu (si host)
    GameClient *client; ///< Client de jeu

    /*METHODE PRIVE*/
    void setUpUI();
    void populate();
    void disableUI();
    void setClient(GameClient *c);
    void setServer(GameServer* s);

};

#endif // LOBBYMENU_H
