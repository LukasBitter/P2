#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPushButton>
class WelcomeWindow;
class SettingsWindow;
class LobbyWindow;
class BasicRTSWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:

    WelcomeWindow* welcomeWindow;
    SettingsWindow* settingsWindow;
    LobbyWindow* lobbyWindow;
    BasicRTSWindow* basicRTSWindow;

private slots:
   void toggleLobbyView();
   void toggleSettingsView();
   void toggleGameView();

};

#endif // MAINWINDOW_H
