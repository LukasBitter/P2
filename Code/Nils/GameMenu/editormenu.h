#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>

class EditView;

namespace GameMenu
{
    class Editor;
}

class EditorMenu : public QWidget
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    EditorMenu(QWidget *parent=0);

    void newView();
private:
    /*OUTIL*/
    EditView *edit;
};

#endif // EDITOR_H
