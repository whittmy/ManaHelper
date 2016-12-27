#include "networkaccessmanager.h"
#include "ui_passworddialog.h"
#include "ui_proxy.h"
#include "downloadui.h"

#include <QtCore/QSettings>

#include <QtGui/QDesktopServices>
#include <QtWidgets/QDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStyle>
#include <QtGui/QTextDocument>

#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkDiskCache>
#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QSslError>

NetworkAccessManager::NetworkAccessManager(QObject *parent)
    : QNetworkAccessManager(parent),
    requestFinishedCount(0), requestFinishedFromCacheCount(0), requestFinishedPipelinedCount(0),
    requestFinishedSecureCount(0), requestFinishedDownloadBufferCount(0)
{
    connect(this, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
            SLOT(authenticationRequired(QNetworkReply*,QAuthenticator*)));
    connect(this, SIGNAL(proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*)),
            SLOT(proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*)));
    connect(this, SIGNAL(finished(QNetworkReply*)),
            SLOT(requestFinished(QNetworkReply*)));
#ifndef QT_NO_OPENSSL
    connect(this, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
            SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
#endif
    loadSettings();

    QNetworkDiskCache *diskCache = new QNetworkDiskCache(this);
    QString location = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    diskCache->setCacheDirectory(location);
    setCache(diskCache);
}

QNetworkReply* NetworkAccessManager::createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData)
{
    QNetworkRequest request = req; // copy so we can modify
    // this is a temporary hack until we properly use the pipelining flags from QtWebkit
    // pipeline everything! :)
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    return QNetworkAccessManager::createRequest(op, request, outgoingData);
}

void NetworkAccessManager::requestFinished(QNetworkReply *reply)
{
    requestFinishedCount++;

    if (reply->attribute(QNetworkRequest::SourceIsFromCacheAttribute).toBool() == true)
        requestFinishedFromCacheCount++;

    if (reply->attribute(QNetworkRequest::HttpPipeliningWasUsedAttribute).toBool() == true)
        requestFinishedPipelinedCount++;

    if (reply->attribute(QNetworkRequest::ConnectionEncryptedAttribute).toBool() == true)
        requestFinishedSecureCount++;

    if (reply->attribute(QNetworkRequest::DownloadBufferAttribute).isValid() == true)
        requestFinishedDownloadBufferCount++;

    if (requestFinishedCount % 10)
        return;

    double pctCached = (double(requestFinishedFromCacheCount) * 100.0/ double(requestFinishedCount));
    double pctPipelined = (double(requestFinishedPipelinedCount) * 100.0/ double(requestFinishedCount));
    double pctSecure = (double(requestFinishedSecureCount) * 100.0/ double(requestFinishedCount));
    double pctDownloadBuffer = (double(requestFinishedDownloadBufferCount) * 100.0/ double(requestFinishedCount));

#ifdef QT_DEBUG
    qDebug("STATS [%lli requests total] [%3.2f%% from cache] [%3.2f%% pipelined] [%3.2f%% SSL/TLS] [%3.2f%% Zerocopy]", requestFinishedCount, pctCached, pctPipelined, pctSecure, pctDownloadBuffer);
#endif
}

void NetworkAccessManager::loadSettings()
{
    QSettings settings;
    settings.beginGroup(QLatin1String("proxy"));
    QNetworkProxy proxy;
    if (settings.value(QLatin1String("enabled"), false).toBool()) {
        if (settings.value(QLatin1String("type"), 0).toInt() == 0)
            proxy = QNetworkProxy::Socks5Proxy;
        else
            proxy = QNetworkProxy::HttpProxy;
        proxy.setHostName(settings.value(QLatin1String("hostName")).toString());
        proxy.setPort(settings.value(QLatin1String("port"), 1080).toInt());
        proxy.setUser(settings.value(QLatin1String("userName")).toString());
        proxy.setPassword(settings.value(QLatin1String("password")).toString());
    }
    setProxy(proxy);
}

void NetworkAccessManager::authenticationRequired(QNetworkReply *reply, QAuthenticator *auth)
{
    //BrowserMainWindow *mainWindow = BrowserApplication::instance()->mainWindow();
    QDialog dialog(0);
    dialog.setWindowFlags(Qt::Sheet);

    Ui::PasswordDialog passwordDialog;
    passwordDialog.setupUi(&dialog);

    passwordDialog.iconLabel->setText(QString());
    passwordDialog.iconLabel->setPixmap(mw->style()->standardIcon(QStyle::SP_MessageBoxQuestion, 0, mw).pixmap(32, 32));

    QString introMessage = tr("<qt>Enter username and password for \"%1\" at %2</qt>");
    introMessage = introMessage.arg(reply->url().toString().toHtmlEscaped()).arg(reply->url().toString().toHtmlEscaped());
    passwordDialog.introLabel->setText(introMessage);
    passwordDialog.introLabel->setWordWrap(true);

    if (dialog.exec() == QDialog::Accepted) {
        auth->setUser(passwordDialog.userNameLineEdit->text());
        auth->setPassword(passwordDialog.passwordLineEdit->text());
    }
}

void NetworkAccessManager::setMainWindow(DownLoadUI *mow){
    mw = mow;
}

void NetworkAccessManager::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *auth)
{
    //BrowserMainWindow *mainWindow = BrowserApplication::instance()->mainWindow();

    QDialog dialog(mw);
    dialog.setWindowFlags(Qt::Sheet);

    Ui::ProxyDialog proxyDialog;
    proxyDialog.setupUi(&dialog);

    proxyDialog.iconLabel->setText(QString());
    proxyDialog.iconLabel->setPixmap(mw->style()->standardIcon(QStyle::SP_MessageBoxQuestion, 0, mw).pixmap(32, 32));

    QString introMessage = tr("<qt>Connect to proxy \"%1\" using:</qt>");
    introMessage = introMessage.arg(proxy.hostName().toHtmlEscaped());
    proxyDialog.introLabel->setText(introMessage);
    proxyDialog.introLabel->setWordWrap(true);

    if (dialog.exec() == QDialog::Accepted) {
        auth->setUser(proxyDialog.userNameLineEdit->text());
        auth->setPassword(proxyDialog.passwordLineEdit->text());
    }
}

#ifndef QT_NO_OPENSSL
void NetworkAccessManager::sslErrors(QNetworkReply *reply, const QList<QSslError> &error)
{
    // check if SSL certificate has been trusted already
    QString replyHost = reply->url().host() + QString(":%1").arg(reply->url().port());
    if(! sslTrustedHostList.contains(replyHost)) {
        //BrowserMainWindow *mainWindow = BrowserApplication::instance()->mainWindow();

        QStringList errorStrings;
        for (int i = 0; i < error.count(); ++i)
            errorStrings += error.at(i).errorString();
        QString errors = errorStrings.join(QLatin1String("\n"));
        int ret = QMessageBox::warning(mw, QCoreApplication::applicationName(),
                tr("SSL Errors:\n\n%1\n\n%2\n\n"
                        "Do you want to ignore these errors for this host?").arg(reply->url().toString()).arg(errors),
                        QMessageBox::Yes | QMessageBox::No,
                        QMessageBox::No);
        if (ret == QMessageBox::Yes) {
            reply->ignoreSslErrors();
            sslTrustedHostList.append(replyHost);
        }
    }
}
#endif
