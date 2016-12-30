#ifndef APPENDIX_H
#define APPENDIX_H

#include <QObject>
#include <QString>

//struct DataReply{
//    QString data;
//};

enum REQ_TYPE{
    UNDEFINED,
    UPGRADE_SELF,
    UPGRADE_DEVICE
};

//定义数据接收的回调函数
typedef void (*_cb_data_func)(REQ_TYPE type, QString data);


class RequestInfo{
public:
    RequestInfo(){
        url = "";
        callback = NULL;
        reqType = UNDEFINED;
    }

    QString url;
    REQ_TYPE reqType;
    _cb_data_func callback;
};


#endif // APPENDIX_H
