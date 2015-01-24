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
    scene = new GameScene(lstGamer, 0, this);
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
        Node *n = new Node(e->x(), e->y(),30,0,lstGamer,0);
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
    QList<Gamer *> l = lstGamer.getLstGamer().values();
    if(m.isValide() && m.getNumberOfSlot() <= l.size())
    {
        scene = new GameScene(m.getCreationString(),lstGamer, 0, this);
        setScene(scene);
        scene->updateFromString(m.getUpdateString());

        for (int i = 0; i < m.getNumberOfSlot(); ++i)
        {
            m.getSlot(i,l.value(i,0));
        }
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
    MapFile m;
}

void EditView::onBtLoadFromFilePressed()
{

}

void EditView::onBtReturnPressed()
{

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

