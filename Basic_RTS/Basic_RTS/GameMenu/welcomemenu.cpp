#include "welcomemenu.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

WelcomeMenu::WelcomeMenu(QWidget *parent) :
    QWidget(parent)
{

    setUpUI();
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void WelcomeMenu::paintEvent(QPaintEvent *)
{
    // AJOUT BACKGROUND

    background.load(":/Background.jpg");

    QPainter painter(this);
    QRectF target(0.0, 0.0, 1280.0, 800.0);
    QRectF source(0.0, 0.0, 1280.0, 800.0);

    painter.drawPixmap(target, background, source);
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void WelcomeMenu::onBtEditorPressed()
{
    emit btEditorPressed();
}

void WelcomeMenu::onBtHostGamePressed()
{
    emit btHostGamePressed();
}

void WelcomeMenu::onBtJointGamePressed()
{
    emit btJointGamePressed();
}

void WelcomeMenu::onBtQuitPressed()
{
    emit btQuitPressed();
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void WelcomeMenu::setUpUI()
{
    //INSTANTIATION

    labelTitle = new QLabel(tr("<h1>BASIC - RTS</h1>"), this);
    btHostGame = new QPushButton(tr("&Host"), this);
    btJoinGame = new QPushButton(tr("&Join"), this);
    btEditor = new QPushButton(tr("&Editor"), this);
    btAbout = new QPushButton(tr("&About"), this);
    btQuit = new QPushButton(tr("&Quit"), this);

    //CONNEXION

    connect(btHostGame,SIGNAL(clicked()),this,SLOT(onBtHostGamePressed()));
    connect(btJoinGame,SIGNAL(clicked()),this,SLOT(onBtJointGamePressed()));
    connect(btEditor,SIGNAL(clicked()),this,SLOT(onBtEditorPressed()));
    connect(btAbout,SIGNAL(clicked()),this,SLOT(onBtAboutPressed()));
    connect(btQuit,SIGNAL(clicked()),this,SLOT(onBtQuitPressed()));

    //AJOUT LAYOUT

    QGridLayout *l = new QGridLayout(this);
    l->addWidget(labelTitle, 0, 0);
    l->addWidget(btHostGame, 5, 0);
    l->addWidget(btJoinGame, 6, 0);
    l->addWidget(btEditor, 7, 0);
    l->addWidget(btAbout, 8, 0);
    l->addWidget(btQuit, 9, 0);
    l->setAlignment(Qt::AlignCenter);

    this->setLayout(l);

    labelTitle->setStyleSheet("color: white; font-size: 16px;");
}


void WelcomeMenu::onBtAboutPressed()
{
    QString msg("<p align='center'><b>V 1.0</b></p><br><br>");
    msg += tr("This game was edited by Nily Riter, Nicolas Gonin and Lukas Bitter<br><br>");
    msg += tr("The purpose of this program is the autumn project in 3rd semester<br>    ");
    msg += tr("HE-Arc Ingéniérie DLM, January 2015");

    QMessageBox::about(this, tr("Informations about the progam"),msg);
}
