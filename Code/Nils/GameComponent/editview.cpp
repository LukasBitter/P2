#include "editview.h"
#include "node.h"
#include "connexion.h"
#include "gamer.h"
#include "gamescene.h"
#include "global.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

EditView::EditView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new GameScene(lstGamer, 0, this);
    setUpUI();
}

EditView::~EditView()
{
    delete scene;
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void EditView::keyPressEvent(QKeyEvent *e)
{
    QGraphicsView::keyPressEvent(e);
    switch (e->key())
    {
    case Qt::Key_1:
        action = EA_ADD;
        break;
    case Qt::Key_2:
        action = EA_REMOVE;
        break;
    default:
        break;
    }
}

void EditView::mousePressEvent(QMouseEvent *e)
{
    if(e->button()== Qt::RightButton)
    {
        switch (action)
        {
        case EA_ADD:
        {
            if(lastSelection != 0 && currentSelection != 0)
            scene->addConnexion(*lastSelection, *currentSelection);
            break;
        }
        case EA_REMOVE:
        {

            break;
        }
        default:
            break;
        }
    }
    else if(e->button()== Qt::LeftButton)
    {
        QGraphicsView::mousePressEvent(e);
        switch (action)
        {
        case EA_ADD:
        {
            Node *n = new Node(e->x(), e->y(),30,0,lstGamer,0);
            scene->addNode(*n);
            break;
        }
        case EA_REMOVE:
        {

            break;
        }
        default:
            break;
        }
    }
}

void EditView::dropEvent(QDropEvent *event)
{

}

/*----------------------------------------------------*/
/*LECTURE-ECRITURE*/
/*----------------------------------------------------*/

void EditView::loadMapName(QString s)
{

}

void EditView::saveMapName(QString s)
{

}

void EditView::selectionChange()
{
    QList<QGraphicsItem *> lst = scene->selectedItems();
    if(!lst.isEmpty())
    {
        lastSelection = currentSelection;
        currentSelection = dynamic_cast <Node*>(lst.first());
    }
    else
    {
        lastSelection = 0;
        currentSelection = 0;
    }
}

void EditView::setUpUI()
{
    setScene(scene);
    connect(scene,SIGNAL(selectionChanged()),this,SLOT(selectionChange()));

    // Désactivation des scrollbars
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setViewportUpdateMode( QGraphicsView::BoundingRectViewportUpdate );
    setRenderHint( QPainter::Antialiasing, true );
}


void EditView::clearMap()
{
    scene->clear();
}
