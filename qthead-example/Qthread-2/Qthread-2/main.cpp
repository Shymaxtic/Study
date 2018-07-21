#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    qDebug()<<"From main thread: "<<QThread::currentThreadId();

    Test test;
    test.DoOutSideThread();
    QThread thread;               //new line
    test.moveToThread(&thread);   //new line
    thread.start();               //new line
    Button btn(&test);
    btn.show();

    return a.exec();
}
