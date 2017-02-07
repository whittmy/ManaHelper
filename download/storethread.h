#ifndef STORETHREAD_H
#define STORETHREAD_H
#include <QObject>
#include <QThread>
#include <QMutex>
class StoreThread : public QThread
{
    Q_OBJECT

public:
    explicit StoreThread(QObject *parent = 0);
    void run();
    void setCopyInfo(qint64 id, QString srcPath, QString destPath);

    bool bComplete();
    qint64 getID();
    QString getSrcPath();
private:

signals:
    void sig_storerlst();
    void sig_storerlst(StoreThread *st);
public slots:


private:
    QString _srcPath, _destPath;
    qint64 _id;
    bool _bComplete;
    QMutex qm;
};

#endif // STORETHREAD_H
