#ifndef LOBBYMENU_H
#define LOBBYMENU_H

#include <QWidget>
#include "GameConnexion/client.h"
#include "GameConnexion/server.h"

class QPushButton;
class QTableView;
class QCheckBox;
class QComboBox;
class QTextEdit;
class QLineEdit;

namespace GameMenu {
    class LobbyMenu;
}

class LobbyMenu : public QWidget
{
    Q_OBJECT
public:
    LobbyMenu(QWidget *parent = 0);

signals:
    void returnToMenu();
    void launchGame();
    void mapSelectionUpdate();

public slots:
    void enableClientUI();
    void enableServerUI();

private slots:
    void connectToServer();
    void updateStatusTable();
    void updateUI();
    void play();
    void onBtReturnPressed();

private:
    QComboBox *cbxMap;
    QCheckBox *cbbReady;
    QPushButton *btStart;
    QTableView *tblStatus;
    QLineEdit *txtAdressIP;
    QPushButton *btConnect;
    QPushButton *btReturn;

    void setUpUI();
    void disableUI();
};

#endif // LOBBYMENU_H
