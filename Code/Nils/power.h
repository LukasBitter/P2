#ifndef POWER_H
#define POWER_H

#include <QObject>

class QTimer;

namespace GameInterface {
    class Power;
}

class Power : public QObject
{
    Q_OBJECT
public:
    Power(int countDown, QObject *parent=0);
    ~Power();
    bool isReady()const;
public slots:
    void activateCountDown();
private slots:
    void restorCountDown();
private:
    QTimer *timer;
    bool ready;
};

#endif // POWER_H
