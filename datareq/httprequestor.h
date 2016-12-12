#ifndef HTTPREQ_H
#define HTTPREQ_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QHash>
#include <QString>
#include <QSignalMapper>

#include "backend/logme.h"
#include "appendix.h"




class HttpRequestor : public QObject
{
    Q_OBJECT
public:
    static HttpRequestor * Instance(QObject *parent=NULL);
    ~HttpRequestor();

    void addTask(PtrRequestInfo req); //传入请求信息，包括回调函数


private slots:
    void slot_replyFinished(QObject*);


private:
    HttpRequestor(QObject *parent=NULL);

private:
    QNetworkAccessManager *m_manager;
    static HttpRequestor * m_http_requestor;
    QHash<QNetworkReply*, PtrRequestInfo> mMap;

    QSignalMapper* _finishedSignalMapper;
    LogMe* _logger;
};

#endif // HTTPREQ_H
