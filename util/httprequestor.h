#ifndef HTTPREQ_H
#define HTTPREQ_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QHash>
#include <QString>
#include <QSignalMapper>

#include "util/logme.h"
#include "appendix.h"




class HttpRequestor : public QObject
{
    Q_OBJECT
public:
    HttpRequestor(QObject *parent=NULL);
    //static HttpRequestor * Instance(QObject *parent=NULL);
    ~HttpRequestor();

    void addTask(RequestInfo *req); //传入请求信息，包括回调函数

signals:
    void sig_onFinished(REQ_TYPE type, QString result);

private slots:
    void slot_replyFinished(QObject*);





private:
    QNetworkAccessManager *m_manager;
    //static HttpRequestor * m_http_requestor;
    QHash<QNetworkReply*, RequestInfo*> mMap;

    QSignalMapper* _finishedSignalMapper;
    LogMe* _logger;
};

#endif // HTTPREQ_H
