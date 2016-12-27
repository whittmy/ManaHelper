#ifndef NETWORKACCESSMANAGER_H
#define NETWORKACCESSMANAGER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include"downloadui.h"
class NetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT

public:
    NetworkAccessManager(QObject *parent = 0);
    DownLoadUI *mw;
    virtual QNetworkReply* createRequest ( Operation op, const QNetworkRequest & req, QIODevice * outgoingData = 0 );
    void setMainWindow(DownLoadUI *mow);

private:
    QList<QString> sslTrustedHostList;
    qint64 requestFinishedCount;
    qint64 requestFinishedFromCacheCount;
    qint64 requestFinishedPipelinedCount;
    qint64 requestFinishedSecureCount;
    qint64 requestFinishedDownloadBufferCount;

public slots:
    void loadSettings();
    void requestFinished(QNetworkReply *reply);

private slots:
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *auth);
    void proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *auth);
#ifndef QT_NO_OPENSSL
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &error);
#endif
};

#endif // NETWORKACCESSMANAGER_H
