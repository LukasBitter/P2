#include "endgamemenu.h"
#include "global.h"

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

void EndGameMenu::enableVictory()
{
    title->setText("Victory");
    QFont f = title->font();
    f.setBold(true);
    f.setPointSize(20);
    title->setFont(f);
    title->setStyleSheet("QLabel { color : green; }");
}

void EndGameMenu::enableDefeat()
{
    title->setText("Defeat");
    QFont f = title->font();
    f.setBold(true);
    f.setPointSize(20);
    title->setFont(f);
    title->setStyleSheet("QLabel { color : red; }");
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
    l->addWidget(title, 0, 0);
    l->addWidget(btReturn, 1, 0);

    this->setLayout(l);
}