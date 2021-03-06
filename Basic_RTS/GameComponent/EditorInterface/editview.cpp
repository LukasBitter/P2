#include "editview.h"
#include "gamer.h"
#include "mapfile.h"
#include "editorinterface.h"
#include "GameComponent/Logic/nodeconnectable.h"
#include "GameComponent/Logic/nodecombat.h"
#include "GameComponent/Logic/nodemana.h"
#include "GameComponent/Logic/connexion.h"
#include "GameComponent/Logic/gamescene.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

EditView::EditView(QWidget *parent) : QGraphicsView(parent),
    scene(0), editorUi(0), memory(0), a(NO_ACTION)
{
    spawnGamer = new Gamer();
    spawnGamer->setColor(Qt::black);
    lstGamer.addGamer(spawnGamer);
    newScene();
    setUpUI();
}

EditView::~EditView()
{
    if(scene != 0) delete scene;
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void EditView::mousePressEvent(QMouseEvent *e)
{
    if(e->button()!= Qt::LeftButton) return;

    switch (a)
    {
    case EA_ADD:
    {
        if(!editorUi->isManaNodeChecked())
        {
            Gamer *g = editorUi->isSpawnNodeChecked() ? spawnGamer : 0;
            NodeCombat *n = new NodeCombat(e->x(), e->y(),20*editorUi->getNodeSize(),
                                           50*editorUi->getNodeSize(),lstGamer,g);
            n->setRessourcesRate(editorUi->getNodeSize());
            n->setRessources(editorUi->getNodeRessource());
            scene->addNode(*n);
        }
        else
        {
            NodeMana *n = new NodeMana(e->x(), e->y(),20*editorUi->getNodeSize(),lstGamer);
            scene->addNode(*n);
        }
        a = NO_ACTION;
        break;
    }
    case EA_REMOVE:
    {
        Node *n = dynamic_cast <Node*>(itemAt(e->pos()));
        if(n != 0) scene->removeNode(*n);
        a = NO_ACTION;
        break;
    }
    case EA_CONNECT:
    {
        NodeConnectable *n = dynamic_cast <NodeConnectable*>(itemAt(e->pos()));
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
        break;
    }
    case EA_DISCONNECT:
    {
        NodeConnectable *n = dynamic_cast <NodeConnectable*>(itemAt(e->pos()));
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
        break;
    }
    default:
        break;
    }

    scene->update(scene->sceneRect());
    QGraphicsView::mousePressEvent(e);
}

/*----------------------------------------------------*/
/*LECTURE-ECRITURE*/
/*----------------------------------------------------*/

void EditView::loadMapName(QString s)
{
    MapFile m;
    m.loadFromFile(s);
    if(m.isValide())
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
    else
    {
        qCritical()<<"EditView : map is not valid";
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
    text = QInputDialog::getText(this, tr("Save the map")
                                         ,tr("Name :"), QLineEdit::Normal,
                                         "", &ok);
    if(ok)
    {
        QString path = QString("%1/%2.%3").arg(MAP_FILE).arg(text).arg(MAP_EXTENSION);
        qDebug()<< path;
        if(QFile(path).exists())
        {
            QMessageBox msgBox;
            msgBox.setText(tr("Map already exist !"));
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
    text = QInputDialog::getText(this, tr("Open map")
                                         ,tr("Name :"), QLineEdit::Normal,
                                         "", &ok);
    if(ok)
    {
        QString path = QString("%1/%2.%3").arg(MAP_FILE).arg(text).arg(MAP_EXTENSION);
        qDebug()<< path;
        if(!QFile(path).exists())
        {
            QMessageBox msgBox;
            msgBox.setText(tr("Map does not exist !"));
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

void EditView::clearMap()
{
    newScene();
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
    connect(editorUi,SIGNAL(btClearPressed()),this,SLOT(clearMap()));
}

void EditView::newScene()
{
    if(scene != 0) delete scene;
    scene = new GameScene(lstGamer, 0, 0);
    setScene(scene);
}

