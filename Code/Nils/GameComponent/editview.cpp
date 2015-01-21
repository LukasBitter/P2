#include "editview.h"
#include "node.h"
#include "connexion.h"
#include "gamer.h"
#include "gamescene.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>

EditView::EditView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new GameScene(lstGamer, 0, this);
    setUpUI();
}

void EditView::setUpUI()
{

}


void EditView::clearMap()
{
    scene->clear();
}
