#ifndef BASICRTSWINDOW_H
#define BASICRTSWINDOW_H

#include <QFrame>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class GameBoard;

class BasicRTSWindow : public QWidget
{
    Q_OBJECT

public:
    BasicRTSWindow(QWidget *parent = 0);
    QPushButton *startButton;
    QPushButton *quitButton;
    GameBoard *board;
private:
    QLabel *createLabel(const QString &text);
    QLabel *scoreLabel;



};

#endif
