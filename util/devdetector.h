#ifndef DEVDETECTOR_H
#define DEVDETECTOR_H

#include <windows.h>
#include <dbt.h>
#include<devguid.h>
#include<SetupAPI.h>
#include<InitGuid.h>
#include <QString>
#include<QObject>
#include "backend/logme.h"

class DevDetector: public QObject
{
    Q_OBJECT
public:
    DevDetector(HANDLE handle, QObject *parent = Q_NULLPTR);
    ~DevDetector();
    void checkDev();
    QString getDevPath();
    bool nativeEvent(const QByteArray & eventType, void * message, long*result);

signals:
    void devConnected(QString path);
    void devRemoved();


private:
    char FirstDriveFromMask (ULONG unitmask);
    void registerListener();
    bool adaptRules(QString drive);

private:
    QString _devPath;
    HANDLE _wnd;
    LogMe *_logger;

};

#endif //
