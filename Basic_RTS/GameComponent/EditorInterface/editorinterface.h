#ifndef EDITORINTERFACE_H
#define EDITORINTERFACE_H

#include "global.h"
#include "enumlibrary.h"

class NodeCombat;

namespace GameInterface
{
    class EditorInterface;
}

/**
 * @class EditorInterface
 * @brief Palette d'outil pour l'edition de map
 */
class EditorInterface : public QWidget
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit EditorInterface(QWidget *parent = 0);

    /*SURCHARGE*/
    void paintEvent(QPaintEvent *);

    /*ASSESSEUR / MUTATEUR*/
    bool isStandardNodeChecked()const;
    bool isSpawnNodeChecked()const;
    bool isManaNodeChecked()const;
    int getNodeSize()const;
    int getNodeRessource()const;

    /*SIGNALS/SLOTS*/
signals:
    void btActionPressed(ACTIONS);
    void btReturnPressed();
    void btSaveToFilePressed();
    void btLoadFromFilePressed();
    void btClearPressed();
private slots:
    void onBtCreateNodePressed();
    void onBtRemoveNodePressed();
    void onBtConnectNodePressed();
    void onBtDisconnectNodePressed();
    void onBtSaveToFilePressed();
    void onBtLoadFromFilePressed();
    void onBtReturnPressed();
    void onBtClearPressed();

private:
    /*INTERFACE*/
    QSpinBox *spRessource;
    QSpinBox *spSize;
    QRadioButton *rbtStandard;
    QRadioButton *rbtSpawn;
    QRadioButton *rbtMana;
    QPushButton *btCreateNode;
    QPushButton *btRemoveNode;
    QPushButton *btConnectNode;
    QPushButton *btDisconnectNode;
    QPushButton *btSaveToFile;
    QPushButton *btLoadFromFile;
    QPushButton *btClear;
    QPushButton *btReturn;
    QPixmap background;

    /*METHODE PRIVE*/
    void setUpUI();
};

#endif // EDITORINTERFACE_H
