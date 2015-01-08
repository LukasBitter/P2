#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QWidget>
class QPushButton;
class WelcomeWindow : public QWidget
{
    Q_OBJECT
public:
    WelcomeWindow(QWidget *parent = 0);
    QPushButton* lobbyButton;
    QPushButton* settingsButton;

private:

signals:

public slots:

};

#endif // WELCOMEWINDOW_H
