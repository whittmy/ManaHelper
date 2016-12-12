#ifndef APPENDIX_H
#define APPENDIX_H

#include <QObject>
#include <QString>

//struct DataReply{
//    QString data;
//};

//定义数据接收的回调函数
typedef void (*_cb_data_func)(QString data);

enum REQ_TYPE{
    UPGRADE_SELF,
    UPGRADE_DEVICE
};

typedef struct struc_RequestInfo{
    QString url;
    REQ_TYPE reqType;
    _cb_data_func callback;
}RequestInfo, *PtrRequestInfo;


#endif // APPENDIX_H
