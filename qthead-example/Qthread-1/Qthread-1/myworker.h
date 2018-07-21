#ifndef MYWORKER_H
#define MYWORKER_H

#include <QObject>
#include <QDebug>
#include <QThread>

class MyWorker : public QObject
{
    Q_OBJECT
public:
    explicit MyWorker(QObject *parent = 0);

signals:

public slots:
    void slotInit() {
        qDebug() << __FUNCTION__ << __LINE__ << QThread::currentThreadId();
    }

};

#endif // MYWORKER_H
