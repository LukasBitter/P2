#include "editormenu.h"
#include "GameComponent/editview.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

EditorMenu::EditorMenu(QWidget *parent) : QWidget(parent)
{
    edit = new EditView(this);
}
