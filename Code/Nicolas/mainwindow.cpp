#include "mainwindow.h"
#include "basicrtswindow.h"
#include "lobbywindow.h"
#include "settingswindow.h"
#include "welcomewindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    welcomeWindow = new WelcomeWindow(this);
    this->setCentralWidget(welcomeWindow);

    settingsWindow = new SettingsWindow(this);
    settingsWindow->setVisible(false);
    lobbyWindow = new LobbyWindow(this);
    lobbyWindow->setVisible(false);
    basicRTSWindow = new BasicRTSWindow(this);
    basicRTSWindow->setVisible(false);
    connect(welcomeWindow->lobbyButton, SIGNAL(clicked()),this, SLOT(toggleLobbyView()));
    connect(welcomeWindow->settingsButton, SIGNAL(clicked()),this, SLOT(toggleSettingsView()));
    connect(lobbyWindow->startButton, SIGNAL(clicked()),this, SLOT(toggleGameView()));
}


MainWindow::~MainWindow()
{
}
void MainWindow::toggleLobbyView()
{
    this->setCentralWidget(lobbyWindow);
    lobbyWindow->setVisible(true);
}
void MainWindow::toggleSettingsView()
{
    this->setCentralWidget(settingsWindow);
    settingsWindow->setVisible(true);
}
void MainWindow::toggleGameView()
{
    this->setCentralWidget(basicRTSWindow);
    basicRTSWindow->setVisible(true);
}

