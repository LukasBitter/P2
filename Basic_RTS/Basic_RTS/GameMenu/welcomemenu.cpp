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

void WelcomeMenu::onBtAboutPressed()
{
    qDebug() << "Bt About";

    QString msg("<p align='center'><b>V 1.0</b><br><br>");
    msg += tr("This game was edited by Nily Riter, Nicolas Gonin and Lukas Bitter<br><br>");
    msg += tr("The purpose of this program is the autumn project in 3rd semester<br></p>    ");
    msg += tr("HE-Arc Ingéniérie DLM, January 2015");


    QMessageBox::about(this, tr("Informations about the progam"),msg);
}

void WelcomeMenu::onBtHelpPressed()
{
    qDebug() << "Bt Help";
    QString fileName(":/README.txt");
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    QMessageBox::information(this, tr("Help - Readme"),content);
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
    btHelp = new QPushButton(tr("Hel&p"), this);
    btAbout = new QPushButton(tr("&About"), this);
    btQuit = new QPushButton(tr("&Quit"), this);

    //CONNEXION

    connect(btHostGame,SIGNAL(clicked()),this,SLOT(onBtHostGamePressed()));
    connect(btJoinGame,SIGNAL(clicked()),this,SLOT(onBtJointGamePressed()));
    connect(btEditor,SIGNAL(clicked()),this,SLOT(onBtEditorPressed()));
    connect(btHelp,SIGNAL(clicked()),this,SLOT(onBtHelpPressed()));
    connect(btAbout,SIGNAL(clicked()),this,SLOT(onBtAboutPressed()));
    connect(btQuit,SIGNAL(clicked()),this,SLOT(onBtQuitPressed()));

    //AJOUT LAYOUT

    QGridLayout *l = new QGridLayout(this);
    l->setColumnStretch(0, 100);
    l->setColumnStretch(1, 1);
    l->setColumnStretch(2, 2);
    l->setColumnStretch(3, 1);
    l->setColumnStretch(4, 100);
    l->addWidget(labelTitle, 0, 1, 1, 3 );
    l->addWidget(btHostGame, 5, 2);
    l->addWidget(btJoinGame, 6, 2);
    l->addWidget(btEditor, 7, 2);
    l->addWidget(btHelp, 8, 2);
    l->addWidget(btAbout, 9, 2);
    l->addWidget(btQuit, 10, 2);
    l->setAlignment(Qt::AlignCenter);

    this->setLayout(l);

    labelTitle->setStyleSheet("color: white; font-size: 16px;");
}
