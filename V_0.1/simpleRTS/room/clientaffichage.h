#ifndef CLIENTAFFICHAGE_H
#define CLIENTAFFICHAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QComboBox;
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class Clientaffichage : public QWidget
{
    Q_OBJECT

    QComboBox *hostCombo;
    QLineEdit *portLineEdit;
    QLineEdit *userNameLineEdit;
    QPushButton *getConnectionButton;
    QPushButton *readyButton;
    QPushButton *runButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QLabel *statusLabel;
    QList<QLabel *> lPlayersNumbers;
    QList<QLabel *> lPlayersNames;
    QList<QLabel *> lPlayersConnected;
    QList<QLabel *> lPlayersReady;

    void setUI();
    void initLabels();
    void updateScreen();

public:
    explicit Clientaffichage(QWidget *parent = 0);


signals:

public slots:

};

#endif // CLIENTAFFICHAGE_H
