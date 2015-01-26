#include "endgamemenu.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

EndGameMenu::EndGameMenu(QWidget *parent) :
    QWidget(parent)
{
    setUpUI();
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void EndGameMenu::onBtReturnPressed()
{
    emit returnToMenu();
}

void EndGameMenu::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRectF target(10.0, 10.0, 800.0, 600.0);

    //painter.drawPixmap(-10, -10, background);
    painter.drawPixmap(target, background, source);
}


void EndGameMenu::enableVictory()
{
    background.load(":/Victory.png");
    source.setRect(0.0, 0.0, 2975.0, 1870.0);
    update();
}

void EndGameMenu::enableDefeat()
{
    background.load(":/Defeat.png");
    source.setRect(0.0, 0.0, 3086.0, 1986.0);
    update();
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void EndGameMenu::setUpUI()
{
    //INSTANTIATION

    btReturn = new QPushButton("Retour", this);
    title = new QLabel("END", this);

    //CONNEXION

    connect(btReturn,SIGNAL(clicked()),this,SLOT(onBtReturnPressed()));

    //AJOUT LAYOUT

    QGridLayout *l = new QGridLayout(this);
    //l->addWidget(title, 0, 0);
    l->addWidget(btReturn, 1, 0);

    this->setLayout(l);
}
