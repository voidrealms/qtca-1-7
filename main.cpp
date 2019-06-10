#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QThreadPool>
#include <QMutex>
#include "counter.h"
#include "worker.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Counter counter;
    QMutex mutex(QMutex::Recursive);
    QThreadPool* pool = QThreadPool::globalInstance();

    qInfo() << "Count: " << counter.count();

    for (int i = 0;i < pool->maxThreadCount();i++)
    {
        Worker* worker = new Worker(&a, &counter,&mutex);
        worker->setAutoDelete(true);
        pool->start(worker);
    }

    pool->waitForDone();

    qInfo() << "Done, the count is: " << counter.count();

    return a.exec();
}
