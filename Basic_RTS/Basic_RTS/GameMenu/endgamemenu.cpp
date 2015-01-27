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
/*SURCHARGE*/
/*----------------------------------------------------*/

void EndGameMenu::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRectF target(10.0, 10.0, 800.0, 600.0);
    QRectF source(0.0, 0.0, 2975.0, 1870.0);

    painter.drawPixmap(target, background, source);
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void EndGameMenu::onBtReturnPressed()
{
    emit returnToMenu();
}

void EndGameMenu::enableVictory()
{
    background.load(":/Victory.png");
    update();
}

void EndGameMenu::enableDefeat()
{
    background.load(":/Defeat.png");
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

//    QGridLayout *l = new QGridLayout(this);
//    l->addWidget(btReturn, 1, 0);

//    this->setLayout(l);
}
