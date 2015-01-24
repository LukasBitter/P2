#ifndef EDITORINTERFACE_H
#define EDITORINTERFACE_H

#include "global.h"
#include "enumlibrary.h"

class Node;
class QPushButton;

namespace GameInterface
{
class EditorInterface;
}

class EditorInterface : public QWidget
{
    Q_OBJECT

public:
    explicit EditorInterface(QWidget *parent = 0);

    /*SIGNALS/SLOTS*/
signals:
    void btActionPressed(ACTIONS);
    void btReturnPressed();
    void btSaveToFilePressed();
    void btLoadFromFilePressed();
private slots:
    void onBtCreateNodePressed();
    void onBtRemoveNodePressed();
    void onBtConnectNodePressed();
    void onBtDisconnectNodePressed();
    void onBtSaveToFilePressed();
    void onBtLoadFromFilePressed();
    void onBtReturnPressed();

private:
    /*INTERFACE*/
    QPushButton *btCreateNode;
    QPushButton *btRemoveNode;
    QPushButton *btConnectNode;
    QPushButton *btDisconnectNode;
    QPushButton *btSaveToFile;
    QPushButton *btLoadFromFile;
    QPushButton *btReturn;

    /*METHODE PRIVE*/
    void setUpUI();
};

#endif // EDITORINTERFACE_H
