#include "editormenu.h"
#include "GameComponent/editview.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

EditorMenu::EditorMenu(QWidget *parent) : QWidget(parent), edit(0)
{
    newView();
}

void EditorMenu::newView()
{
    qDebug()<<"EditorMenu : enter 'newView'";
    if(edit != 0)
    {
        qDebug()<<"EditorMenu : delete map";
        delete edit;
    }
    edit = new EditView(this);
}
