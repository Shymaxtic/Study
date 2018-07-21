#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include <QPushButton>
#include <QObject>
#include <QEvent>
#include <QThread>
#include <QMainWindow>
#include <QCoreApplication>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
/*****************************************************************************************************************************/
class Test : public QObject
{
    Q_OBJECT
protected:
    bool event(QEvent *evt)
    {
        if (evt->type() == QEvent::User) {
            qDebug()<<"Event received in thread"<<QThread::currentThreadId();
            for(unsigned int i = 0; i < 99; i++) {
                qDebug() << i;
                QThread::msleep(100);
            }
            return true;
        }
        return QObject::event(evt);
    }
    void run() {
        qDebug() << "RUN in thread: " << QThread::currentThreadId();
        for(unsigned int i = 0; i < 200; i++) {
            qDebug() << "RUN: " << i;
            QThread::msleep(100);
        }
    }
public:
    void functionOutSide() {
        qDebug() << "functionOutSide: in thread " << QThread::currentThreadId();
    }

public slots:
    void slotDoInsideThread() {
        qDebug()<<"slotDoInsideThread: Event received in thread"<<QThread::currentThreadId();
        m_Thread = new PriThread(this);
        m_Thread->start();
        for(unsigned int i = 0; i < 100; i++) {
            qDebug() << __FUNCTION__ << __LINE__ << i;
            QThread::msleep(100);
        }
    }
    void slotDoInsideThread2() {
        qDebug() << "slotDoInsideThread2: Event received in thread" << QThread::currentThreadId();
        for(unsigned int i = 0; i < 100; i++) {
            qDebug() << __FUNCTION__ << __LINE__ <<i;
            QThread::msleep(100);
        }
    }

public:
    void DoOutSideThread() {
        qDebug() << "Do something befor go into thread" << "-> Current Thread: " << QThread::currentThreadId();
    }
private:
    class PriThread: public QThread
    {
    public:
        PriThread( Test *parent):
            parent( parent )
        {}
        ~PriThread(){}
    private:
        Test * parent;

    protected:
        void run()
        {
            if(!parent) return;
            parent->run();
            exit(0);
        }
    };
    friend class PriThread;
    PriThread * m_Thread;
};
/*****************************************************************************************************/
class Button : public QPushButton
{
    Q_OBJECT
    Test *m_test;
public:
    Button(Test *test):QPushButton("Send Event"), m_test(test)
    {
//        connect(this, SIGNAL(clicked()), SLOT(onClicked()));
        connect(this, SIGNAL(pressed()), m_test, SLOT(slotDoInsideThread()));
//        connect(this, SIGNAL(released()), m_test, SLOT(slotDoInsideThread2()));
    }

//private slots:
//    void onClicked()
//    {
//        QCoreApplication::postEvent(m_test, new QEvent(QEvent::User));
//    }
protected:
    void mouseReleaseEvent(QMouseEvent* e) {
        m_test->functionOutSide();
        QPushButton::mouseReleaseEvent(e);
    }
};
#endif // MAINWINDOW_H
