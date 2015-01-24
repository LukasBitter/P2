#include "editview.h"
#include "node.h"
#include "connexion.h"
#include "gamer.h"
#include "gamescene.h"
#include "mapfile.h"
#include "GameInterface/editorinterface.h"
#include "GameInterface/powerinterface.h"
#include "global.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

EditView::EditView(QWidget *parent) : QGraphicsView(parent),
    scene(0), editorUi(0), memory(0), a(NO_ACTION)
{
    spawnGamer = new Gamer();
    spawnGamer->setColor(Qt::gray);
    lstGamer.addGamer(spawnGamer);
    scene = new GameScene(lstGamer, 0, 0);
    setScene(scene);
    setUpUI();
}

EditView::~EditView()
{
    delete scene;
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void EditView::mousePressEvent(QMouseEvent *e)
{
    if(e->button()!= Qt::LeftButton) return;

    if(a == EA_ADD)
    {
        Gamer *g = editorUi->isSpawnNodeChecked() ? spawnGamer : 0;
        Node *n = new Node(e->x(), e->y(),20*editorUi->getNodeSize(),
                           50*editorUi->getNodeSize(),lstGamer,g);
        n->setRessourcesRate(editorUi->getNodeSize());
        n->setRessources(editorUi->getNodeRessource());
        scene->addNode(*n);
        a = NO_ACTION;
    }
    else if(a == EA_REMOVE)
    {
        Node *n = dynamic_cast <Node*>(itemAt(e->pos()));
        if(n != 0) scene->removeNode(*n);
        a = NO_ACTION;
    }
    else if(a == EA_CONNECT)
    {
        Node *n = dynamic_cast <Node*>(itemAt(e->pos()));
        if(n != 0)
        {
            if(memory != 0)
            {
                scene->addConnexion(*memory,*n);
                a = NO_ACTION;
                memory = 0;
            }
            else
            {
                memory = n;
            }
        }

    }
    else if(a == EA_DISCONNECT)
    {
        Node *n = dynamic_cast <Node*>(itemAt(e->pos()));
        if(n != 0)
        {
            if(memory != 0)
            {
                scene->removeConnexion(*memory,*n);
                a = NO_ACTION;
                memory = 0;
            }
            else
            {
                memory = n;
            }
        }
    }
    scene->update(scene->sceneRect());
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

void EditView::clearMap()
{
    scene->clear();
}

/*----------------------------------------------------*/
/*LECTURE-ECRITURE*/
/*----------------------------------------------------*/

void EditView::loadMapName(QString s)
{
    MapFile m;
    m.loadFromFile(s);
    if(m.isValide() && m.getNumberOfSlot() <= MAX_GAMER)
    {
        delete scene;
        scene = new GameScene(m.getCreationString(),lstGamer, 0, this);
        setScene(scene);
        scene->updateFromString(m.getUpdateString());

        for (int i = 0; i < m.getNumberOfSlot(); ++i)
        {
            scene->updateFromString(m.getSlot(i,spawnGamer));
        }
        scene->update(scene->sceneRect());
    }
}

void EditView::saveMapName(QString s)
{
    MapFile m;
    m.setVersion(VERSION_MAP);
    foreach (QString s, scene->normalizeSpawn())
    {
        m.addSlot(s);
    }
    m.setCreationString(scene->getCreationString());
    m.setUpdateString(scene->getUpdateString());
    m.saveToFile(s);
    loadMapName(s);
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void EditView::onBtActionPressed(ACTIONS a)
{
    this->a = a;
}

void EditView::onBtSaveToFilePressed()
{
    bool ok;
    QString text;
    text = QInputDialog::getText(this, tr("Sauver la map")
                                         ,tr("Nom :"), QLineEdit::Normal,
                                         "", &ok);
    if(ok)
    {
        QString path = QString("%1/%2.%3").arg(MAP_FILE).arg(text).arg(MAP_EXTENSION);
        qDebug()<< path;
        if(QFile(path).exists())
        {
            QMessageBox msgBox;
            msgBox.setText("La map existe déjà !");
            msgBox.exec();
        }
        else
        {
            saveMapName(path);
        }
    }
}

void EditView::onBtLoadFromFilePressed()
{

    bool ok;
    QString text;
    text = QInputDialog::getText(this, tr("Ouvrir la map")
                                         ,tr("Nom :"), QLineEdit::Normal,
                                         "", &ok);
    if(ok)
    {
        QString path = QString("%1/%2.%3").arg(MAP_FILE).arg(text).arg(MAP_EXTENSION);
        qDebug()<< path;
        if(!QFile(path).exists())
        {
            QMessageBox msgBox;
            msgBox.setText("La map n'existe pas !");
            msgBox.exec();
        }
        else
        {
            loadMapName(path);
        }
    }
}

void EditView::onBtReturnPressed()
{
    qDebug()<<"EditView : want switch to menu";
    emit returnToMenu();
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void EditView::setUpUI()
{
    editorUi = new EditorInterface(this);

    // Désactivation des scrollbars
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setViewportUpdateMode( QGraphicsView::BoundingRectViewportUpdate );
    setRenderHint( QPainter::Antialiasing, true );

    connect(editorUi,SIGNAL(btActionPressed(ACTIONS)),this,SLOT(onBtActionPressed(ACTIONS)));
    connect(editorUi,SIGNAL(btReturnPressed()),this,SLOT(onBtReturnPressed()));
    connect(editorUi,SIGNAL(btLoadFromFilePressed()),this,SLOT(onBtLoadFromFilePressed()));
    connect(editorUi,SIGNAL(btSaveToFilePressed()),this,SLOT(onBtSaveToFilePressed()));
}

