#include "httpRequestor.h"
#include <QTextCodec>
#include <QDebug>

//请求url列表。
QString gUrlArr[] = {
    "", //nothing
    "http://www.nybgjd.com/update/api2/handler?apk_vercode=&board=&android=&time=&upmode=&mac=00&brand=LEMOON&firmware=00.01.01&device=PiaPia", //UPGRADE_SELF
    "http://www.sohu.com"   //UPGRADE_DEVICE
};


//静态成员变量初始化
//HttpRequestor* HttpRequestor::m_http_requestor = NULL;


HttpRequestor::HttpRequestor(QObject *parent)
    :QObject(parent),_logger(new LogMe(this))
{
    m_manager = new QNetworkAccessManager(this);


    _finishedSignalMapper = new QSignalMapper(this);

}

HttpRequestor::~HttpRequestor(){
    if(m_manager != NULL)
        delete m_manager;

    if(_finishedSignalMapper != NULL)
        delete _finishedSignalMapper;

    //???
//    if(m_http_requestor != NULL)
//        delete m_http_requestor;
}





//HttpRequestor * HttpRequestor::Instance(QObject *parent){
//    if(m_http_requestor == NULL)
//        m_http_requestor = new HttpRequestor(parent);
//    return m_http_requestor;
//}


//该函数important， 同类批量信号槽操作。
void HttpRequestor::addTask(RequestInfo *info){
    _logger->info("addTask "+ info->url);
    //url.setEncodedUrl()
    QNetworkRequest request(QUrl(info->url));
    QNetworkReply *reply = m_manager->get(request);

    QHash<QNetworkReply*,RequestInfo*>::iterator i =  mMap.insert(reply, info);
    _finishedSignalMapper->setMapping(i.key(), i.key());

    connect(i.key(), SIGNAL(finished()), _finishedSignalMapper, SLOT(map()));
    connect(_finishedSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(slot_replyFinished(QObject*)));

    //delete info; !!!!!!
}

void HttpRequestor::slot_replyFinished(QObject* obj){
    _logger->info("slot_replyFinished");

    QNetworkReply *reply = qobject_cast<QNetworkReply*>(obj);

    QTextCodec *codec = QTextCodec::codecForName("utf8");
    //使用utf8编码, 这样可以显示中文
    QString str = codec->toUnicode(reply->readAll());
    //qDebug() << "++++++return: " << str.size() << str;
    reply->deleteLater();//最后要释放replay对象


    QHash<QNetworkReply*,RequestInfo*>::iterator i = mMap.find(reply);
    if(i != mMap.end()){
        _logger->info("find the reply");
        if(i.value()->callback != NULL)
            i.value()->callback(i.value()->reqType, str);

        //信号发送
        emit sig_onFinished(i.value()->reqType, str/*, i.value()*/);


        //--------------
        //RequestInfo这信息暂时不用，即便使用，也不能在这儿释放，否则槽函数会有机会得到无效值
        //delete i.value();
        mMap.remove(i.key());
    }
}




