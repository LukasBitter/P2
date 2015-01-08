#include <QtWidgets>

#include "basicrtswindow.h"
#include "gameboard.h"



BasicRTSWindow::BasicRTSWindow(QWidget *parent) :
                               QWidget(parent)
{
    board = new GameBoard();

    scoreLabel = new QLabel;
    scoreLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    scoreLabel->setAlignment(Qt::AlignCenter);
    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);

    connect(startButton, SIGNAL(clicked()), board, SLOT(start()));
    connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createLabel(tr("SCORE")), 0, 0);
    layout->addWidget(scoreLabel, 1, 0);
    layout->addWidget(startButton, 4, 0);
    layout->addWidget(board, 0, 1, 6, 1);
    layout->addWidget(quitButton, 4, 2);
    setLayout(layout);

    setWindowTitle(tr("Basic RTS"));
    resize(550, 500);
}
QLabel *BasicRTSWindow::createLabel(const QString &text)
{
    QLabel *lbl = new QLabel(text);
    lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return lbl;
}

